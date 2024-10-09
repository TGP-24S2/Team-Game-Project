#include "sceneFFgame.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "animatedsprite.h"
#include "enemy.h"
#include "player.h"
#include "inputsystem.h"
#include "iniparser.h"
#include "imgui.h"
#include "weapon.h"
#include "particleemitter.h"
#include "melee.h"
#include "inlinehelpers.h"
#include "rectanglemaker.h"
#include "collision.h"
#include <typeinfo>
#include <iostream>
#include <math.h>

SceneFFGame::SceneFFGame()
	: m_fLocalDeltaTime(0.0f)
	, m_fTimeSinceInput(0.0f)
	, m_pPlayer(nullptr)
	, m_lpEnemies(nullptr)
	, m_iNumEnemies(0)
	, m_pCursorSprite(nullptr)
	, m_pGameOverSprite(nullptr)
{
}

SceneFFGame::~SceneFFGame()
{
	delete m_pPlayer;
	delete m_pCursorSprite;
	delete m_pGameOverSprite;
	for (int i = 0; i < m_iNumEnemies; i++)
	{
		delete m_lpEnemies[i];
	}
}

bool SceneFFGame::Initialise(Renderer& renderer, SoundSystem* soundSystem)
{
	renderer.SetClearColour(255, 255, 255);

	m_pPlayer = new Player();
	m_pPlayer->Initialise(renderer);

	weapons = IniParser::GetInstance().GetWeapons("config.ini"); //weapon vector
	m_iCurrentWeapon = 1;

	m_lpEnemies = new Enemy*[10];
	m_iNumEnemies = 0;

	Enemy* pTestEnemy = new Enemy();
	pTestEnemy->Initialise(renderer, "sprites\\ballAnimated.png");
	pTestEnemy->SetPlayer(m_pPlayer);
	m_lpEnemies[m_iNumEnemies++] = pTestEnemy;

	m_pCursorSprite = renderer.CreateSprite("sprites\\crosshair.png");
	m_pCursorSprite->SetScale(1.0f);

	m_pGameOverSprite = renderer.CreateSprite("sprites\\gameover.png");
	m_pGameOverSprite->SetScale(0.5f);
	m_pGameOverSprite->SetX(600);
	m_pGameOverSprite->SetY(200);

	m_pRectangle = new Rectangle();
	m_pRectangle->setHeight(100.0f);
	m_pRectangle->setLength(100.0f);

	m_pRectangle->setPosition(1.0f,1.0f);
	m_pRectangle->setColor(0.0f, 0.0f, 0.0f);


	return true;
}

void SceneFFGame::Process(float deltaTime, InputSystem& inputSystem)
{
	//update timer
	m_fTimeSinceInput += deltaTime;

	//End game if player dies
	if (!m_pPlayer->IsAlive())
	{
		return;
	}

	//Player aim:
	m_cursorPosition = inputSystem.GetMousePosition();
	m_pCursorSprite->SetX(static_cast<int>(m_cursorPosition.x));
	m_pCursorSprite->SetY(static_cast<int>(m_cursorPosition.y));

	//Player self:
	ButtonState leftMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_A));
	ButtonState rightMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_D));
	ButtonState upMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_W));
	ButtonState downMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_S));
	ButtonState mouse1State = (inputSystem.GetMouseButtonState(1));

	// Check input for time buffer:
	// 
	// Note: This approach becomes unrealistic if more controls continue to be added
	//		 Consider actively just checking if input occurs from any classes using InputSystem
	if (leftMoveState == BS_HELD)	m_fTimeSinceInput = 0;
	if (rightMoveState == BS_HELD)	m_fTimeSinceInput = 0;
	if (upMoveState == BS_HELD)		m_fTimeSinceInput = 0;
	if (downMoveState == BS_HELD)	m_fTimeSinceInput = 0;
	if (mouse1State == BS_PRESSED)	m_fTimeSinceInput = 0;

	//Game Logic:
	float ratio = 1.0f - (m_fTimeSinceInput / m_fPostMovementTimeBuffer);
	if (ratio < 0.0f)
		ratio = 0.0f; //prevent negative values
	m_fLocalDeltaTime = deltaTime * ratio;

	// process entities
	for (int i = 0; i < m_iNumEnemies; i++)
		m_lpEnemies[i]->Process(m_fLocalDeltaTime);
	m_pPlayer->Process(m_fLocalDeltaTime, inputSystem);
	m_pCursorSprite->Process(m_fLocalDeltaTime);

	//calculate angle towards crosshair
	float angle = atan2(m_pCursorSprite->GetY() - m_pPlayer->GetY(), m_pCursorSprite->GetX() - m_pPlayer->GetX());
	
	//offset to player
	float offsetX = 80 * cos(angle);
	float offsetY = 80 * sin(angle);

	m_pPlayer->SetAimAngle(angle);
	
	//aims towards crosshair + convert to degrees
	weapons[m_iCurrentWeapon]->SetAngle(angle * 180.0f / (float)M_PI);
	
	//ensures the weapon is attached to player location with offset towards cursor
	weapons[m_iCurrentWeapon]->SetXY(m_pPlayer->GetX() + offsetX, m_pPlayer->GetY() + offsetY);
	
	weapons[m_iCurrentWeapon]->Process(m_fLocalDeltaTime);

	// Hitbox processing
	float playerX = m_pPlayer->GetX();
	float playerY = m_pPlayer->GetY();
	// process player vs enemy collision
	for (int i = 0; i < m_iNumEnemies; i++)
	{
		Enemy* pEnemy = m_lpEnemies[i];
		const double circleSquareRatio = M_PI / 4.0;
		int ballSize = (int)(Entity::BALL_SIZE * circleSquareRatio) + 1;
		bool colliding = Collision::CheckSizedSpritesColliding
		(
			m_pPlayer->GetSprite(), ballSize,
			pEnemy->GetSprite(), ballSize
		);
		if (colliding)
		{
			m_pPlayer->TakeDamage();
		}
	}
	// weapon processing
	for (const Weapon* weapon : weapons)
	{

	}

}

void SceneFFGame::Draw(Renderer& renderer)
{
	// draw all entities (order matters)
	for (int i = 0; i < m_iNumEnemies; i++)
		m_lpEnemies[i]->Draw(renderer);
	m_pPlayer->Draw(renderer);
	m_pCursorSprite->Draw(renderer);
	weapons[m_iCurrentWeapon]->Draw(renderer);
	if (!m_pPlayer->IsAlive())
		m_pGameOverSprite->Draw(renderer);
	m_pRectangle->draw();
}

void SceneFFGame::DebugDraw()
{
	ImGui::Text("Weapons:");
	for (Weapon* weapon : weapons) {
		ImGui::Text(weapon->GetWeaponName().c_str());
	}

	weapons[m_iCurrentWeapon]->DebugDraw();
}

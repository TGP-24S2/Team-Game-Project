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
#include "particle.h" 
#include "particleemitter.h"
#include "collision.h"
#include "inlinehelpers.h"
#include "rectangle.h"
#include "soundsystem.h"

#include <typeinfo>
#include <iostream>
#include <math.h>

SceneFFGame::SceneFFGame()
	: m_fLocalDeltaTime(0.0f)
	, m_fTimeSinceInput(0.0f)
	, m_pRenderer(nullptr)
	, m_pSoundSystem(nullptr)
	, m_pPlayer(nullptr)
	, m_lpEnemies(nullptr)
	, m_iNumEnemies(0)
	, m_pCursorSprite(nullptr)
	, m_pTestBall(nullptr)
	, m_pGameOverSprite(nullptr)
	, m_pYouWinSprite(nullptr)
	, m_pRectangle(nullptr)
	, m_eStatus()
	, m_iCurrentWeapon(0)
{
}

SceneFFGame::~SceneFFGame()
{
	WipeScene();
}

void SceneFFGame::WipeScene()
{
	delete m_pPlayer;
	delete m_pCursorSprite;
	delete m_pGameOverSprite;
	delete m_pYouWinSprite;
	for (int i = 0; i < m_iNumEnemies; i++)
	{
		delete m_lpEnemies[i];
	}

	m_pPlayer = nullptr;
	m_pCursorSprite = nullptr;
	m_pGameOverSprite = nullptr;
	m_pYouWinSprite = nullptr;
	for (int i = 0; i < m_iNumEnemies; i++)
	{
		m_lpEnemies[i] = nullptr;
	}
	m_iNumEnemies = 0;
}

bool SceneFFGame::Initialise(Renderer& renderer, SoundSystem* soundSystem)
{
	m_pRenderer = &renderer;
	m_pSoundSystem = soundSystem;

	m_eStatus = GS_RUNNING;

	renderer.SetClearColour(255, 255, 255);

	m_pPlayer = new Player();
	m_pPlayer->Initialise(renderer);

	weapons = IniParser::GetInstance().GetWeapons("config.ini"); //weapon vector
	m_iCurrentWeapon = 0;

	m_lpEnemies = new Enemy*[10];
	m_iNumEnemies = 0;

	Enemy* pTestEnemy = new Enemy();
	pTestEnemy->Initialise(renderer);
	pTestEnemy->SetPlayer(m_pPlayer);
	m_lpEnemies[m_iNumEnemies++] = pTestEnemy;

	m_pCursorSprite = renderer.CreateSprite("sprites\\crosshair.png");
	m_pCursorSprite->SetScale(1.0f);

	m_pGameOverSprite = renderer.CreateSprite("sprites\\gameover.png");
	m_pGameOverSprite->SetScale(0.5f);
	m_pGameOverSprite->SetX(600);
	m_pGameOverSprite->SetY(200);

	m_pYouWinSprite = renderer.CreateSprite("sprites\\victory.png");
	m_pYouWinSprite->SetScale(0.5f);
	m_pYouWinSprite->SetX(600);
	m_pYouWinSprite->SetY(200);

	m_pRectangle = new Rectangle();
	m_pRectangle->height = 10.0f;
	m_pRectangle->width = 10.0f;

	m_pRectangle->setPosition(0.0f,0.0f);
	m_pRectangle->setColor(1.0f, 0.0f, 0.0f);

	//sounds
	soundSystem->LoadSound("sounds\\BM_GameLoopMusic4.mp3", false, true);
	soundSystem->PlaySound("sounds\\BM_GameLoopMusic4.mp3");
	soundSystem->LoadSound("sounds\\SE-LaserHit.wav");
	soundSystem->LoadSound("sounds\\SE-EnemyExplosion.wav");

	return true;
}

void SceneFFGame::Process(float deltaTime, InputSystem& inputSystem)
{
	//update timer
	m_fTimeSinceInput += deltaTime;

	GameStatus lastStatus = m_eStatus;

	// set game status
	if (!m_pPlayer->IsAlive())
		m_eStatus = GS_LOSS;
	int numEnemies = 0;
	for (int i = 0; i < m_iNumEnemies; i++)
		if (m_lpEnemies[i]->IsAlive())
			numEnemies++;
	if (numEnemies == 0)
		m_eStatus = GS_WIN;

	if ((m_eStatus == GS_WIN || m_eStatus == GS_LOSS)
		&&lastStatus == GS_RUNNING)
	{
		m_pSoundSystem->PlaySound("sounds\\SE-EnemyExplosion.wav");
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
	ButtonState gameRestartState = (inputSystem.GetKeyState(SDL_SCANCODE_RETURN));
	ButtonState mouse1State = (inputSystem.GetMouseButtonState(1));
	ButtonState weaponOneState = (inputSystem.GetKeyState(SDL_SCANCODE_1));
	ButtonState weaponTwoState = (inputSystem.GetKeyState(SDL_SCANCODE_2));
	ButtonState weaponThreeState = (inputSystem.GetKeyState(SDL_SCANCODE_3));

	// Check input for time buffer:
	// 
	// Note: This approach becomes unrealistic if more controls continue to be added
	//		 Consider actively just checking if input occurs from any classes using InputSystem
	if (leftMoveState == BS_HELD)	m_fTimeSinceInput = 0;
	if (rightMoveState == BS_HELD)	m_fTimeSinceInput = 0;
	if (upMoveState == BS_HELD)		m_fTimeSinceInput = 0;
	if (downMoveState == BS_HELD)	m_fTimeSinceInput = 0;
	if (mouse1State == BS_PRESSED)	m_fTimeSinceInput = 0;

	if (weaponOneState == BS_PRESSED) m_iCurrentWeapon = 0;
	if (weaponTwoState == BS_PRESSED) m_iCurrentWeapon = 1;
	if (weaponThreeState == BS_PRESSED) m_iCurrentWeapon = 2;

	// restart on keypress
	if (gameRestartState == BS_RELEASED)
	{
		WipeScene();
		Initialise(*m_pRenderer, m_pSoundSystem);
	}

	//Exit here if game is complete
	if (m_eStatus != GS_RUNNING)
		return;

	// sound when attacking
	if (mouse1State == BS_PRESSED) {
		m_pSoundSystem->PlaySound("sounds\\SE-LaserHit.wav");
	}

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
	if (weapons[m_iCurrentWeapon]->GetWeaponType() == 0) { //gun
		weapons[m_iCurrentWeapon]->SetXY(m_pPlayer->GetX() + offsetX, m_pPlayer->GetY() + offsetY);
	}
	else if (weapons[m_iCurrentWeapon]->GetWeaponType() == 1) { //melee
		weapons[m_iCurrentWeapon]->SetXY(m_pPlayer->GetX(), m_pPlayer->GetY());
	}

	m_pPlayer->SetWeaponType(weapons[m_iCurrentWeapon]->GetWeaponType());
	
	weapons[m_iCurrentWeapon]->Process(m_fLocalDeltaTime);

	// Hitbox processing
	float playerX = m_pPlayer->GetX();
	float playerY = m_pPlayer->GetY();
	// process collision with enemies
	for (int i = 0; i < m_iNumEnemies; i++)
	{
		Enemy* pEnemy = m_lpEnemies[i];

		// check collision with player
		if (Collision::CheckSpriteCollision(m_pPlayer->GetSprite(), pEnemy->GetSprite()))
		{
			m_pPlayer->TakeDamage(pEnemy->GetDamage());
		}

		// check weapon->bullet collision
		for (const auto weapon : weapons)
		{
			auto bullets = weapon->GetParticles();
			auto damage = weapon->GetDamage();
			// check hitbox of each bullet
			for (const auto bullet : bullets)
			{
				if (Collision::CheckSpriteCollision(bullet->GetSprite(), pEnemy->GetSprite()))
				{
					// enemy damage when hit
					pEnemy->TakeDamage(damage);
				}
			}
		}
	}

}

void SceneFFGame::Draw(Renderer& renderer)
{
	// draw all entities (order matters)
	for (int i = 0; i < m_iNumEnemies; i++)
	{
		m_lpEnemies[i]->Draw(renderer);
	}

	m_pPlayer->Draw(renderer);
	m_pCursorSprite->Draw(renderer);

	weapons[m_iCurrentWeapon]->Draw(renderer);

	if (m_eStatus == GS_WIN)
		m_pYouWinSprite->Draw(renderer);
	if (m_eStatus == GS_LOSS)
		m_pGameOverSprite->Draw(renderer);

	m_pRectangle->Draw(renderer);
}

void SceneFFGame::DebugDraw()
{
	ImGui::Text("Weapons:");
	for (ParticleEmitter* weapon : weapons) {
		ImGui::Text(weapon->GetWeaponName().c_str());
	}

	weapons[m_iCurrentWeapon]->DebugDraw();
}

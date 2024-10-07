#include "sceneFFgame.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "enemy.h"
#include "player.h"
#include "inputsystem.h"
#include "iniparser.h"

SceneFFGame::SceneFFGame()
	: m_fLocalDeltaTime(0.0f)
	, m_fTimeSinceInput(0.0f)
	, m_pPlayer(nullptr)
	, m_pCursorSprite(nullptr)
	, m_pTestEnemy(nullptr)
{
}

SceneFFGame::~SceneFFGame()
{
	delete m_pPlayer;
	delete m_pCursorSprite;
}

bool SceneFFGame::Initialise(Renderer& renderer, SoundSystem* soundSystem)
{
	renderer.SetClearColour(255, 255, 255);

	m_pPlayer = new Player();
	m_pPlayer->Initialise(renderer);

	weapons = IniParser::GetInstance().GetWeapons("config.ini"); //weapon vector

	m_pTestEnemy = new Enemy();
	m_pTestEnemy->Initialise(renderer, "sprites\\ballAnimated.png");
	m_pTestEnemy->SetPlayer(m_pPlayer);

	m_pCursorSprite = renderer.CreateSprite("sprites\\crosshair.png");
	m_pCursorSprite->SetScale(1.0f);

	m_pCursorSprite->SetScale(0.25f);

	return true;
}

void SceneFFGame::Process(float deltaTime, InputSystem& inputSystem)
{
	//update timer
	m_fTimeSinceInput += deltaTime;

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
	if (leftMoveState == BS_HELD)	m_fTimeSinceInput = 0;
	if (rightMoveState == BS_HELD)	m_fTimeSinceInput = 0;
	if (upMoveState == BS_HELD)		m_fTimeSinceInput = 0;
	if (downMoveState == BS_HELD)	m_fTimeSinceInput = 0;
	if (mouse1State == BS_PRESSED)	m_fTimeSinceInput = 0;

	//Game Logic:
	float ratio = 1.0f - (m_fTimeSinceInput / m_fPostMovementTimeBuffer);
	if (ratio < 0.0f)
	{
		ratio = 0.0f; //prevent negative values
	}
	m_fLocalDeltaTime = deltaTime * ratio;


	m_pPlayer->Process(m_fLocalDeltaTime, inputSystem);

	m_pCursorSprite->Process(m_fLocalDeltaTime);

	m_pTestEnemy->Process(m_fLocalDeltaTime);
}

void SceneFFGame::Draw(Renderer& renderer)
{
	m_pPlayer->Draw(renderer);
	m_pCursorSprite->Draw(renderer);
	m_pTestEnemy->Draw(renderer);
}

void SceneFFGame::DebugDraw()
{
}

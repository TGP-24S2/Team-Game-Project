#include "sceneFFgame.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "animatedsprite.h"
#include "level.h"
#include "enemy.h"
#include "player.h"
#include "inputsystem.h"
#include "iniparser.h"
#include "imgui.h"
#include "particle.h"
#include "weapon.h"
#include "collision.h"
#include "inlinehelpers.h"
#include "rectangle.h"
#include "soundsystem.h"
#include "Prop.h"
#include "PropTemplate.h"
#include "ammopickup.h"

#include <typeinfo>
#include <iostream>
#include <math.h>
#include <map>

SceneFFGame::SceneFFGame()
	: m_fLocalDeltaTime(0.0f)
	, m_fTimeSinceInput(0.0f)
	, m_pRenderer(nullptr)
	, m_pSoundSystem(nullptr)
	, m_pLevel(nullptr)
	, m_pPlayer(nullptr)
	, m_pCursorSprite(nullptr)
	, m_pTestBall(nullptr)
	, m_Props{0,0,0,0,0}
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

	m_pPlayer = nullptr;
	m_pCursorSprite = nullptr;
	m_pGameOverSprite = nullptr;
	m_pYouWinSprite = nullptr;

	m_vpEnemies.clear();
	m_vpAmmoPickups.clear();
}

bool SceneFFGame::Initialise(Renderer& renderer, SoundSystem* soundSystem)
{
	m_pRenderer = &renderer;
	m_pSoundSystem = soundSystem;

	m_eStatus = GS_RUNNING;

	renderer.SetClearColour(255, 255, 255);

	m_pLevel = new Level("levels\\examplelevel.txt");
	std::vector<Rectangle *> hitboxes;
	int nrow = 0;
	for (std::vector<enum LevelCell> rowsvec : m_pLevel->GetLevelData())
	{
		int ncell = 0;
		for (enum LevelCell cell : rowsvec)
		{
			switch (cell)
			{
				case LC_WALL:
				{
					const int CELL_SIZE = 20;
					int x = ncell * CELL_SIZE;
					int y = nrow * CELL_SIZE;
					Sprite *pSprite = renderer.CreateSprite("sprites\\box.png");
					pSprite->SetScale(0.1f);
					pSprite->SetX(x);
					pSprite->SetY(y);
					m_vpPropSprites.push_back(pSprite);

					Rectangle* rect = new Rectangle();
					Vector2* pos = new Vector2((float)x, (float)y);
					rect->setPosition(*pos);
					rect->width = (float)pSprite->GetWidth();
					rect->height = (float)pSprite->GetHeight();
					hitboxes.push_back(rect);
				}
				case LC_E:
					// idk
				case LC_P:
					// idk
				default:
					break;
			}

			ncell++;
		}
		nrow++;
	}
	Entity::SetEnvHitboxes(hitboxes);
	// remove any enemies that spawn inside player
	for (auto pEnemy : m_vpEnemies)
	{
		if (Collision::CheckRectangleCollision(pEnemy->GetHitbox(), m_pPlayer->GetHitbox()))
		{
			pEnemy->Kill();
		}
	}

	m_pPlayer = new Player();
	m_pPlayer->Initialise(renderer);

	m_vpWeapons = IniParser::GetInstance().GetWeapons("config.ini"); //weapon vector
	m_iCurrentWeapon = 0;
	for (auto weapon : m_vpWeapons)
	{
		m_vpWeaponIconSprites.push_back(weapon->GetIconSprite());
	}

	// random num of enemies
	for (int i = 0; i < GetRandom(1, 5); i++)
	{
		Enemy* pTestEnemy = new Enemy(m_pPlayer);
		pTestEnemy->Initialise(renderer);
		m_vpEnemies.push_back(pTestEnemy);
	}

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

	for (int i = 0; i < MAX_PROPS; i++)
	{
		m_Props[i] = new Prop();
		m_Props[i]->Initialise(renderer);
	}

	m_PropTemplates = IniParser::GetInstance().GetPropTemplates("config.ini");
	SpawnProps();

	// HUD
	m_pHud.Initialise(renderer);
	m_pHud.SetPlayer(m_pPlayer);

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
	for (auto pEnemy : m_vpEnemies)
		if (pEnemy->IsAlive())
			numEnemies++;
	if (numEnemies == 0)
		m_eStatus = GS_WIN;

	if ((m_eStatus == GS_WIN || m_eStatus == GS_LOSS)
		&&lastStatus == GS_RUNNING)
	{
		m_pSoundSystem->PlaySound("sounds\\SE-EnemyExplosion.wav");
	}

	// Level environment
	for (Sprite* pSprite : m_vpPropSprites)
		pSprite->Process(deltaTime);

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
	for (auto pEnemy : m_vpEnemies)
		pEnemy->Process(m_fLocalDeltaTime);
	m_pPlayer->Process(m_fLocalDeltaTime, inputSystem); // process user input too
	m_pCursorSprite->Process(m_fLocalDeltaTime);

	//calculate angle towards crosshair
	float angle = atan2(m_pCursorSprite->GetY() - m_pPlayer->GetY(), m_pCursorSprite->GetX() - m_pPlayer->GetX());
	
	//offset to player
	float offsetX = 80 * cos(angle);
	float offsetY = 80 * sin(angle);

	m_pPlayer->SetAimAngle(angle);
	
	//aims towards crosshair + convert to degrees
	m_vpWeapons[m_iCurrentWeapon]->SetAngle(angle * 180.0f / (float)M_PI);
	
	//ensures the weapon is attached to player location with offset towards cursor
	if (m_vpWeapons[m_iCurrentWeapon]->GetWeaponType() == GUN) { //gun
		m_vpWeapons[m_iCurrentWeapon]->SetXY(m_pPlayer->GetX() + offsetX, m_pPlayer->GetY() + offsetY);
	}
	else if (m_vpWeapons[m_iCurrentWeapon]->GetWeaponType() == MELEE) { //melee
		m_vpWeapons[m_iCurrentWeapon]->SetXY(m_pPlayer->GetX(), m_pPlayer->GetY());
	}

	// Weapons:
	m_pPlayer->SetWeaponType(m_vpWeapons[m_iCurrentWeapon]->GetWeaponType());
	m_pPlayer->SetCurrentAmmo(m_vpWeapons[m_iCurrentWeapon]->GetAmmoCount());
	m_vpWeapons[m_iCurrentWeapon]->Process(m_fLocalDeltaTime);
	m_vpWeaponIconSprites[m_iCurrentWeapon]->Process(m_fLocalDeltaTime);
	m_pHud.UpdateWeapon(m_vpWeapons[m_iCurrentWeapon]);

	// Hitbox processing
	float playerX = m_pPlayer->GetX();
	float playerY = m_pPlayer->GetY();
	// process collision with enemies
	for (auto pEnemy : m_vpEnemies)
	{
		if (!pEnemy->IsAlive())
		{
			continue;
		}

		// check collision with player
		if (Collision::CheckRectangleCollision(m_pPlayer->GetHitbox(), pEnemy->GetHitbox()))
		{
			m_pPlayer->TakeDamage(pEnemy->GetDamage());
		}

		// check weapon->bullet collision
		for (const auto weapon : m_vpWeapons)
		{
			auto bullets = weapon->GetParticles();
			auto damage = weapon->GetDamage();
			// check hitbox of each bullet
			for (const auto bullet : bullets)
			{
				if (Collision::CheckRectangleCollision(bullet->GetHitbox(), pEnemy->GetHitbox()))
				{
					// enemy damage when hit
					pEnemy->TakeDamage(damage);
				}
			}
		}

		pEnemy->SetSpeedScale(1.0f); // default if no collision
		for (auto prop : m_Props)
		{
			if (!prop->m_bIsAlive)
			{
				continue;
			}

			// Check for collision
			if (Collision::CheckPointInRectangle(pEnemy->GetPosition(), prop->m_hitbox))
			{
				pEnemy->SetSpeedScale(prop->m_pTemplate->m_fMaxSpeedScale);
				break; //checking point in rectangle, will only ever collide with one
			}
		}
	}

	// prop / player collision
	m_pPlayer->SetSpeedProfile(1.0f, 1.0f, 1.0f); // default if no collision
	for (auto prop : m_Props)
	{
		if (!prop->m_bIsAlive)
		{
			continue;
		}

		// Check for collision
		if (Collision::CheckPointInRectangle(m_pPlayer->GetPosition(), prop->m_hitbox))
		{
			m_pPlayer->SetSpeedProfile(
				prop->m_pTemplate->m_fAccelScale,
				prop->m_pTemplate->m_fDecelScale,
				prop->m_pTemplate->m_fMaxSpeedScale
			);
			break; //checking point in rectangle, will only ever collide with one
		}
	}

	if (GetRandom(1,10000) == 1)
	{
		AmmoPickup* ammopickup =new AmmoPickup(*m_pRenderer);
		m_vpAmmoPickups.push_back(ammopickup);
	}

	for (AmmoPickup* ammopickup : m_vpAmmoPickups)
	{
		if (ammopickup->IsAlive())
		{
			ammopickup->GetSprite()->Process(deltaTime);
			if (Collision::CheckSpriteCollision(m_pPlayer->GetSprite(), ammopickup->GetSprite()))
			{
				m_vpWeapons[m_iCurrentWeapon]->AddAmmo(ammopickup->m_iAmmoCount);
				ammopickup->Kill();
			}
		}
	}

	// hud
	m_pHud.Process(m_fLocalDeltaTime);
}

void SceneFFGame::Draw(Renderer& renderer)
{
	// draw all entities (order matters)

	// drawing in reverse:
	// prop collisions will detect first in the array,
	// so earlier props are drawn later to better reflect collision
	for (int i = MAX_PROPS - 1; i >= 0; i--)
	{
		if (m_Props[i]->m_bIsAlive)
		{
			m_Props[i]->Draw(renderer);
		}
	}

	// Level environment
	for (Sprite* pSprite : m_vpPropSprites)
		pSprite->Draw(renderer);

	for (Enemy* pEnemy : m_vpEnemies)
		pEnemy->Draw(renderer);

	m_pPlayer->Draw(renderer);
	m_pCursorSprite->Draw(renderer);

	if (m_eStatus == GS_RUNNING)
	{
		m_vpWeapons[m_iCurrentWeapon]->Draw(renderer);
		m_vpWeaponIconSprites[m_iCurrentWeapon]->Draw(renderer);
	}

	for (AmmoPickup* ammopickup : m_vpAmmoPickups)
	{
		if (ammopickup->IsAlive())
		{
			ammopickup->GetSprite()->Draw(renderer);
		}
	}

	if (m_eStatus == GS_WIN)
		m_pYouWinSprite->Draw(renderer);
	if (m_eStatus == GS_LOSS)
		m_pGameOverSprite->Draw(renderer);

	m_pHud.Draw(renderer);
}

void SceneFFGame::DebugDraw()
{
	ImGui::Text("Weapons:");
	for (Weapon *weapon : m_vpWeapons)
	{
		ImGui::Text(weapon->GetWeaponName().c_str());
	}

	m_pPlayer->DebugDraw();
	m_vpWeapons[m_iCurrentWeapon]->DebugDraw();
}

Prop* SceneFFGame::GetPropPoolObject()
{
	for (int i = 0; i < MAX_PROPS; i++)
	{
		if (!m_Props[i]->m_bIsAlive)
		{
			return m_Props[i];
		}
	}

	//if no available obstacle instances return null
	return nullptr;
}

void SceneFFGame::SpawnProps()
{
	for (PropTemplate* prop : m_PropTemplates)
	{
		if (GetRandom(0, 1))
		{
			Prop* p = GetPropPoolObject();
			if (p != nullptr)
			{
				p->SetTemplate(prop);
				p->m_bIsAlive = true;
				p->Spawn();
			}
		}
	}
}

float SceneFFGame::UpdateDifficultyModifier()
{
	// DIFFICULTY ALGORITHM:
	// 30% : Player Current Health Ratio
	// 50% : Amount of Cleared Levels
	// 20% : Player's Current Amount of Ammo Mags

	float playerHealthRatio = 0.3 * (m_pPlayer->GetHealthRatio());
	float levelProgress = 0.5 * (m_iCompletedLevels / m_iTotalLevels);

	int numMags = 0;
	for (auto weapon : m_vpWeapons)
	{
		if (weapon->GetWeaponType() == weaponType(GUN))
		{
			numMags += (weapon->GetMagCount());
		}
	}
	float ammoRatio = 0.2 * std::min((float)numMags, (float)MAGAZINE_DIFFICULTY_CAP) / (float)MAGAZINE_DIFFICULTY_CAP;

	return 1 + playerHealthRatio + levelProgress + ammoRatio;
}

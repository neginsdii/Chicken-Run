#include "GameBoard.h"
#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"
#include "GameEngine/Util/CameraManager.h"
#include "Game/GameEntities/PlayerEntity.h"
#include "Game/GameEntities/ObstacleEntity.h"
#include "Game/GameEntities/bgEntity.h"
#include <iostream>
#include<cstdlib>
#include<ctime>

#define WINDOW_HEIGHT  832
#define WINDOW_WIDTH 1280

using namespace Game;

GameBoard::GameBoard()
	: m_player(nullptr)
	, m_backGround(nullptr)
	, m_lastObstacleSpawnTimer(0.f)
	, m_isGameOver(false)
	,numberOfEnemies(5)
	,b_win(false)
{
	m_player = new PlayerEntity();
	counter = 0;
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);
	m_player->SetPos(sf::Vector2f(64.f, 128.f));	
	m_player->SetSize(sf::Vector2f(64.f, 64.f));

	m_light = new LightEntity();

	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_light);
	m_light->SetPos(sf::Vector2f(70.f, 130.f));
	m_light->SetSize(sf::Vector2f(3000.f, 3000.f));
	
	CreateBackGround();
	createObstacles();
	createHealth();
	
	playerPos = m_player->GetPos();

}


GameBoard::~GameBoard()
{

}


void GameBoard::Update()
{	

	float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
	if (!m_isGameOver)
	{
		m_lastObstacleSpawnTimer -= dt;
		

		UpdateObstacles(dt);
		UpdateLight();
		
		UpdatePlayerDying();
		checkCollision(dt);
		if (m_healths.size() == 0)
			m_isGameOver = true;

	}	
	else
	{
		if (!m_gameOver){
			m_gameOver = new GameOver();

		GameEngine::GameEngineMain::GetInstance()->AddEntity(m_gameOver);
		m_player->getSoundComponent()->PlaySound(m_player->getSoundComponent()->LoadSoundFromFile("Resources/snd/error.ogg"), false);
		m_gameOver->SetPos(sf::Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT/2));
		m_gameOver->SetSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
		}
	}
	if (b_win) {
		if (!m_win) {
			m_win = new win();

			GameEngine::GameEngineMain::GetInstance()->AddEntity(m_win);
		//	m_player->getSoundComponent()->PlaySound(m_player->getSoundComponent()->LoadSoundFromFile("Resources/snd/win.wav"),false);
			m_win->SetPos(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
			m_win->SetSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
		}
	}
}

void GameBoard::UpdateLight()
{
	m_light->SetPos(sf::Vector2f(m_player->GetPos().x+5, m_player->GetPos().y + 10));
}


void GameBoard::UpdateHealth()
{
	if (m_healths.size() > 0) {
		std::vector<GameEngine::Entity*>::iterator it = m_healths.begin();
		GameEngine::Entity* health = (*it);


		GameEngine::GameEngineMain::GetInstance()->RemoveEntity(health);
		it = m_healths.erase(it);
		for(int i =0;i<1000;i++)
		{ }

	}
}


void GameBoard::UpdatePlayerDying()
{	
	bool noGameOver = GameEngine::CameraManager::IsFollowCameraEnabled();

	if (noGameOver)
		return;

	static float xToPlayerDie = 0.f;
	if (m_player->GetPos().x < xToPlayerDie)
	{
		m_isGameOver = true;
	}
}


void GameBoard::SpawnNewRandomObstacles()
{
	static float minNextSpawnTime = 0.3f;
	static float maxNextSpawnTime = 0.7f;

	static float minObstacleXPos = 50.f;
	static float maxObstacleXPos = 450.f;
	static float minObstacleYPos = 20.f;
	static float maxObstacleYPos = 450.f;
	
	static float minObstacleHeight = 50.f;
	static float maxObstacleHeight = 170.f;
	static float minObstacleWidth = 20.f;
	static float maxObstacleWidth = 40.f;

	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));
	sf::Vector2f size = sf::Vector2f(RandomFloatRange(minObstacleWidth, maxObstacleWidth), RandomFloatRange(minObstacleHeight, maxObstacleHeight));

	SpawnNewObstacle(pos, size);

	m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);
}


void GameBoard::createObstacles()
{
	
	int bgMapArr[35][14] = {
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,1,0,0,1,0,0,0,0,0,1,0,0,1},
							{1,1,0,1,0,0,0,1,0,1,0,0,0,1},
							{1,1,0,1,0,0,1,0,2,1,0,1,0,1},
							{1,1,0,0,0,0,1,0,0,0,1,0,0,1},
							{1,1,1,0,0,0,0,0,1,0,0,0,1,1},
							{1,1,0,0,1,0,0,0,0,1,0,0,0,1},
							{1,1,0,0,0,0,1,0,0,0,0,1,0,1},
							{1,1,0,1,1,1,0,0,1,0,0,0,1,1},
							{1,1,0,0,0,0,0,0,1,0,1,0,0,1},
							{1,1,1,1,0,1,0,0,0,1,0,0,1,1},
							{1,1,0,2,0,1,0,0,0,0,0,1,0,1},
							{1,1,1,1,1,1,1,1,0,0,1,0,0,1},
							{1,1,0,0,0,1,0,0,0,1,0,1,0,1},
							{1,1,0,1,0,0,0,1,0,0,0,0,1,1},
							{1,1,0,0,1,1,0,0,1,1,0,0,0,1},
							{1,1,1,0,1,0,0,1,0,0,1,1,0,1},
							{1,1,0,0,0,0,1,2,0,0,0,0,0,1},
							{1,1,0,1,1,0,0,0,0,1,0,1,1,1},
							{1,1,0,0,0,1,1,1,0,0,0,0,0,1},
							{1,1,1,0,1,0,0,0,1,1,0,0,0,1},
							{1,1,0,0,0,1,0,0,0,0,1,0,1,1},
							{1,1,0,1,0,0,0,1,1,0,0,0,1,1},
							{1,1,0,0,0,1,0,0,0,1,1,1,0,1},
							{1,1,1,1,0,0,0,1,0,0,0,0,0,1},
							{1,1,0,0,1,1,0,0,1,1,0,1,0,1},
							{1,1,1,0,0,0,0,0,0,0,0,0,0,1},
							{1,1,0,0,1,2,1,1,0,0,0,1,1,1},
							{1,1,1,0,1,0,0,0,1,0,1,0,0,1},
							{1,1,0,0,0,0,1,0,0,0,0,0,0,1},
							{1,1,1,1,0,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,0,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,9,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,1,1,1,1,1,1,1,1,1,1,1,1,2} };
	sf::Vector2f pos = sf::Vector2f(0.0f,0.0f);	
	sf::Vector2f size = sf::Vector2f(64.f, 64.f);
	int cnt = 0;
	for (int a = 0; a < 35; ++a)
	{
		for (int b = 0; b < 14; ++b)
		{
			if (bgMapArr[a][b] == 1)
			{
				ObstacleEntity* obstacle = new ObstacleEntity();
				GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);
				obstacle->SetPos(sf::Vector2f(a*size.x, b * size.y));
				obstacle->SetSize(sf::Vector2f(size.x, size.y));

				m_obstacles.push_back(obstacle);
			}
			else if (bgMapArr[a][b] == 9) {
				endPoint = new EndpointEntity();
				GameEngine::GameEngineMain::GetInstance()->AddEntity(endPoint);
				endPoint->SetPos(sf::Vector2f(a * size.x, b * size.y));
				endPoint->SetSize(sf::Vector2f(size.x, size.y));

			}
			else if (bgMapArr[a][b] == 2) 	
			{
					createEnemies(a * size.x, b * size.y);
				
				
			}
		}
	}
	
}

void GameBoard::createEnemies(int x, int y)
{
	sf::Vector2f size = sf::Vector2f(64.f, 64.f);
	EnemyEntity* enemy = new EnemyEntity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(enemy);
	enemy->SetPos(sf::Vector2f(x, y));
	enemy->SetSize(sf::Vector2f(size.x, size.y));

	m_enemies.push_back(enemy);
}

void GameBoard::createHealth()
{
	sf::Vector2f pos = sf::Vector2f(40.0f, 20.0f);
	sf::Vector2f size = sf::Vector2f(32.f, 32.f);

	for (int b = 0; b < 3; ++b)
	{
		HealthEntity *health = new HealthEntity();
			GameEngine::GameEngineMain::GetInstance()->AddEntity(health);
			health->SetPos(sf::Vector2f(b * size.x+pos.x, pos.y));
			health->SetSize(sf::Vector2f(size.x, size.y));

			m_healths.push_back(health);
		

	}
}


void GameBoard::SpawnNewObstacle(const sf::Vector2f& pos, const sf::Vector2f& size)
{
	ObstacleEntity* obstacle = new ObstacleEntity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);
	obstacle->SetPos(pos);
	obstacle->SetSize(sf::Vector2f(size.x, size.y));

	m_obstacles.push_back(obstacle);
}

void GameBoard::checkCollision(float dt)
{
	if (m_enemies.size() > 0) {
		for (std::vector<GameEngine::Entity*>::iterator it = m_enemies.begin(); it != m_enemies.end();)
		{

			GameEngine::Entity* enemy = (*it);
			if (m_player->GetPos().x<enemy->GetPos().x + enemy->GetSize().x - 10 &&
				m_player->GetPos().x + m_player->GetSize().x - 10 > enemy->GetPos().x &&
				m_player->GetPos().y<enemy->GetPos().y + enemy->GetSize().y - 10 &&
				m_player->GetPos().y + m_player->GetSize().y - 10 > enemy->GetPos().y)
			{
				GameEngine::GameEngineMain::GetInstance()->RemoveEntity(enemy);
				m_player->getSoundComponent()->PlaySound(m_player->getSoundComponent()->LoadSoundFromFile("Resources/snd/pig.ogg"),true);
				it = m_enemies.erase(it);
				UpdateHealth();
				
				
			}
			else
			{

				float disX = m_player->GetPos().x - enemy->GetPos().x;
				float disY = m_player->GetPos().y - enemy->GetPos().y;
				float distance = sqrt(pow(disX, 2) + pow(disY, 2));
				if (distance < 200)
				{
					enemy->SetPos(sf::Vector2f(enemy->GetPos().x + (m_player->GetPos().x - enemy->GetPos().x) * 0.22 / distance,
						enemy->GetPos().y + (m_player->GetPos().y - enemy->GetPos().y) * 0.22 / distance));
				}
			}
			if (m_enemies.size() > 0)
				it++;
			else
				break;

		}
	}
		std::cout << m_player->GetPos().x << std::endl;
		std::cout << endPoint->GetPos().x << std::endl;
	if (m_player->GetPos().x<endPoint->GetPos().x + endPoint->GetSize().x - 10 &&
		m_player->GetPos().x + m_player->GetSize().x - 10 > endPoint->GetPos().x &&
		m_player->GetPos().y<endPoint->GetPos().y + endPoint->GetSize().y - 10 &&
		m_player->GetPos().y + m_player->GetSize().y - 10 > endPoint->GetPos().y)
	{
		std::cout << "win" << std::endl;
		b_win = true;
	}
	
	counter++;
}


void GameBoard::CreateBackGround()
{

	sf::Vector2f pos = sf::Vector2f(0.0f,0.0f);
	sf::Vector2f size = sf::Vector2f(64.f, 64.f);

	for (int a = 0; a < 35; ++a)
	{
		pos.y = 0;
		pos.x = a * size.x;
		for (int b = 0; b < 14; ++b)
		{

			bgEntity* bgTile = new bgEntity();
			GameEngine::GameEngineMain::GetInstance()->AddEntity(bgTile);
			bgTile->SetPos(pos);
			bgTile->SetSize(sf::Vector2f(size.x, size.y));

			m_bgTiles.push_back(bgTile);
			pos.y += size.y;
		}
	}
}


void GameBoard::UpdateObstacles(float dt)
{


	if(m_player->GetPos().x !=playerPos.x )
	{
		if (m_player->GetPos().x >= WINDOW_WIDTH/5)
		{
			
			for (std::vector<GameEngine::Entity*>::iterator it = m_obstacles.begin(); it != m_obstacles.end();)
			{
				GameEngine::Entity* obstacle = (*it);
				sf::Vector2f currPos = obstacle->GetPos();
				currPos.x += (playerPos.x - (m_player->GetPos().x)) ;
				obstacle->SetPos(currPos);
				
				it++;

			}
			if (m_enemies.size() > 0) {
				for (std::vector<GameEngine::Entity*>::iterator it = m_enemies.begin(); it != m_enemies.end();)
				{
					GameEngine::Entity* enemy = (*it);
					sf::Vector2f currPos = enemy->GetPos();
					currPos.x += (playerPos.x - (m_player->GetPos().x));
					enemy->SetPos(currPos);
					//enemy->GetComponent<GameEngine::CollidableComponent>().
					if (m_enemies.size() > 0) 
						it++;
					else
						break;
				}
			}
			
			sf::Vector2f currPos = endPoint->GetPos();
			currPos.x += (playerPos.x - (m_player->GetPos().x));
			endPoint->SetPos(currPos);
			endPoint->SetPos(currPos);
			

		}
	}
		playerPos = m_player->GetPos();

}



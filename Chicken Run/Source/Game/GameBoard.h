#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "Game/GameEntities/LightEntity.h"
#include "Game/GameEntities/HealthEntity.h"
#include "Game/GameEntities/EnemyEntity.h"
#include "Game/GameEntities/EndpointEntity.h"
#include "Game/GameEntities/GameOver.h"
#include "Game/GameEntities/win.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace Game
{
	//Used for storing and controling all game related entities
	class PlayerEntity;	

	class GameBoard
	{
	public:
		GameBoard();
		virtual ~GameBoard();

		//Temp - for nice architecture this should be within some sort of IUpdatable interface that GameEngine handles (so that not only entities can be updated)
		void Update();
		void UpdateLight();
		void UpdateHealth();
		void UpdateObstacles(float dt);
		
		void UpdatePlayerDying();
		void SpawnNewRandomObstacles();
		void createObstacles();
		void createEnemies(int x, int y);
		void createHealth();
		void SpawnNewObstacle(const sf::Vector2f& pos, const sf::Vector2f& size);
		void checkCollision(float dt);
		bool IsGameOver() const { return m_isGameOver; }		

	protected:
		//Placeholder temp - should go to helpers or smth.
		float RandomFloatRange(float a, float b)
		{
			return ((b - a) * ((float)rand() / RAND_MAX)) + a;
		}

		void CreateBackGround();
		int counter = 0;
		PlayerEntity* m_player;
		GameOver* m_gameOver;
		win* m_win;
		bool b_win;
		LightEntity* m_light;
		HealthEntity* m_health;
		int numberOfEnemies;
		GameEngine::Entity* m_backGround;
		sf::Vector2f playerPos;
		EndpointEntity* endPoint;
		GameEngine::Entity* soundEntity;
		GameEngine::SoundComponent* soundComponent;
		std::vector<GameEngine::Entity*> m_enemies;
		std::vector<GameEngine::Entity*> m_obstacles;
		std::vector<GameEngine::Entity*> m_healths;
		std::vector<GameEngine::Entity*> m_bgTiles;
		float m_lastObstacleSpawnTimer;
		bool  m_isGameOver;
	};
}


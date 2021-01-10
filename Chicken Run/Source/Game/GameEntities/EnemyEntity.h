#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/AnimationComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "Game/GameComponents/PlayerMovementComponent.h"

namespace Game
{

	class EnemyEntity : public GameEngine::Entity
	{
	public:
		EnemyEntity();
		~EnemyEntity();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;

	protected:
		GameEngine::SpriteRenderComponent* m_renderComponent;
		PlayerMovementComponent* m_playerMovementComponent;
		GameEngine::AnimationComponent* m_animComponent;
	};
}


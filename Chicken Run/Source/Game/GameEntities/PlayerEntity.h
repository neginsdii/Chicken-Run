#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/AnimationComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "Game/GameComponents/PlayerMovementComponent.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"

namespace Game
{			

	class PlayerEntity : public GameEngine::Entity
	{
	public:
		PlayerEntity();
		~PlayerEntity();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;
		GameEngine::SoundComponent* getSoundComponent() { return soundComponent2; }
	protected:
		GameEngine::SpriteRenderComponent* m_renderComponent;		
		PlayerMovementComponent*	 m_playerMovementComponent;
		GameEngine::AnimationComponent* m_animComponent;
		GameEngine::SoundComponent* soundComponent ;
		GameEngine::SoundComponent* soundComponent2;
	};
}


#include "PlayerEntity.h"

#include "Game/GameComponents/PlayerSoundComponent.h"
#include "Game/GameComponents/PlayerCameraComponent.h"

#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"
#include "GameEngine/EntitySystem/Components/ParticleEmitterComponent.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"
#include "GameEngine/Util/AnimationManager.h"

using namespace Game;

PlayerEntity::PlayerEntity()
{
	//Movement
	m_playerMovementComponent = AddComponent<PlayerMovementComponent>();

	//Render 
	m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();	
	m_renderComponent->SetTexture(GameEngine::eTexture::Player);
	m_renderComponent->SetZLevel(3);

	//Animation
	m_animComponent = AddComponent<GameEngine::AnimationComponent>();
		
	//Collisions
	AddComponent<GameEngine::CollidablePhysicsComponent>();
	
	
	//Sound
	 soundComponent = AddComponent<GameEngine::SoundComponent>();
	soundComponent->SetNumSimultaneousSounds(1); // Hard coded 5 simultaneous sounds for the player
	soundComponent2 = AddComponent<GameEngine::SoundComponent>();
	soundComponent2->SetNumSimultaneousSounds(1); // Hard coded 5 simultaneous sounds for the player

	//Camera control
	AddComponent<PlayerCameraComponent>();
}

 
PlayerEntity::~PlayerEntity()
{

}


void PlayerEntity::OnAddToWorld()
{
	Entity::OnAddToWorld();
	//soundComponent->PlaySound(soundComponent->LoadSoundFromFile("Resources/snd/music.wav"));
	
	if (m_animComponent)
	{
		m_animComponent->PlayAnim(GameEngine::EAnimationId::BirdIdle);
	}
}


void PlayerEntity::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}

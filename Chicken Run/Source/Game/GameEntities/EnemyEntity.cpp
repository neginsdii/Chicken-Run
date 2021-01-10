#include "EnemyEntity.h"

#include "Game/GameComponents/PlayerSoundComponent.h"
#include "Game/GameComponents/PlayerCameraComponent.h"

#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"
#include "GameEngine/EntitySystem/Components/ParticleEmitterComponent.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"
#include "GameEngine/Util/AnimationManager.h"

using namespace Game;

EnemyEntity::EnemyEntity()
{
	//Movement
//	m_playerMovementComponent = AddComponent<PlayerMovementComponent>();

	//Render 
	m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	m_renderComponent->SetTexture(GameEngine::eTexture::enemy);
	m_renderComponent->SetZLevel(2);

	//Animation
	m_animComponent = AddComponent<GameEngine::AnimationComponent>();
	m_animComponent->PlayAnim(GameEngine::EAnimationId::Enemy);
	//Collisions
	//AddComponent<GameEngine::CollidableComponent>();


}


EnemyEntity::~EnemyEntity()
{

}


void EnemyEntity::OnAddToWorld()
{
	Entity::OnAddToWorld();
//	m_animComponent->PlayAnim(GameEngine::EAnimationId::Enemy);
	if (m_animComponent)
	{
	//	m_animComponent->PlayAnim(GameEngine::EAnimationId::BirdIdle);
	}
}


void EnemyEntity::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}

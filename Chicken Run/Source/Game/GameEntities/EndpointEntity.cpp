#include "EndpointEntity.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/Util/AnimationManager.h"

#include <SFML/Graphics.hpp>

using namespace Game;

EndpointEntity::EndpointEntity()
{
	endPoint = false;
	m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	m_renderComponent->SetFillColor(sf::Color::Red);
	m_renderComponent->SetTexture(GameEngine::eTexture::flag);
	m_renderComponent->SetZLevel(1);
	m_renderComponent->SetTileIndex(0, 0);
	m_animComponent = AddComponent<GameEngine::AnimationComponent>();
	m_animComponent->PlayAnim(GameEngine::EAnimationId::flag);
	//AddComponent<GameEngine::CollidableComponent>();
}


EndpointEntity::~EndpointEntity()
{

}


void EndpointEntity::OnAddToWorld()
{
	Entity::OnAddToWorld();
}


void EndpointEntity::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}

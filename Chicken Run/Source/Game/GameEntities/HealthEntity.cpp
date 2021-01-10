#include "HealthEntity.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

#include <SFML/Graphics.hpp>

using namespace Game;

HealthEntity::HealthEntity()
{
	m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	m_renderComponent->SetFillColor(sf::Color::Red);
	m_renderComponent->SetTexture(GameEngine::eTexture::health);
	m_renderComponent->SetZLevel(4);
	//	m_renderComponent->SetTileIndex(0, 0);


}


HealthEntity::~HealthEntity()
{

}


void HealthEntity::OnAddToWorld()
{
	Entity::OnAddToWorld();
}


void HealthEntity::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}

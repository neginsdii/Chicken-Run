#include "LightEntity.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

#include <SFML/Graphics.hpp>

using namespace Game;

LightEntity::LightEntity()
{
	m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	m_renderComponent->SetFillColor(sf::Color::Red);
	m_renderComponent->SetTexture(GameEngine::eTexture::Light);
	m_renderComponent->SetZLevel(3);
//	m_renderComponent->SetTileIndex(0, 0);


}


LightEntity::~LightEntity()
{

}


void LightEntity::OnAddToWorld()
{
	Entity::OnAddToWorld();
}


void LightEntity::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}

#include "bgEntity.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

#include <SFML/Graphics.hpp>

using namespace Game;

bgEntity::bgEntity()
{
	m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	m_renderComponent->SetFillColor(sf::Color::Red);
	m_renderComponent->SetTexture(GameEngine::eTexture::BG);
	m_renderComponent->SetZLevel(0);
//	m_renderComponent->SetTileIndex(0, 0);


}


bgEntity::~bgEntity()
{

}


void bgEntity::OnAddToWorld()
{
	Entity::OnAddToWorld();
}


void bgEntity::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}

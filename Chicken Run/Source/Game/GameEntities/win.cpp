#include "win.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

#include <SFML/Graphics.hpp>

using namespace Game;

win::win()
{
	m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	m_renderComponent->SetFillColor(sf::Color::Red);
	m_renderComponent->SetTexture(GameEngine::eTexture::win);
	m_renderComponent->SetZLevel(5);
	//	m_renderComponent->SetTileIndex(0, 0);


}


win::~win()
{

}


void win::OnAddToWorld()
{
	Entity::OnAddToWorld();
}


void win::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}

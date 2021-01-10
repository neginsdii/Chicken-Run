#include "GameOver.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

#include <SFML/Graphics.hpp>

using namespace Game;

GameOver::GameOver()
{
	m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	m_renderComponent->SetFillColor(sf::Color::Red);
	m_renderComponent->SetTexture(GameEngine::eTexture::gameover);
	m_renderComponent->SetZLevel(5);
	//	m_renderComponent->SetTileIndex(0, 0);


}


GameOver::~GameOver()
{

}


void GameOver::OnAddToWorld()
{
	Entity::OnAddToWorld();
}


void GameOver::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}

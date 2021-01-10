#pragma once
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameEngine
{
	//TODO - if needed, move out of Engine part to some sort of loader on the game side of things
	namespace eTexture
	{
		enum type
		{
			None = -1,
			Player = 0,
			Tileset,
			BG,
			Particles,
			Light,
			health,
			enemy,
			flag,
			food,
			gameover,
			win,
			Count,
		};
	}	

	inline const char* GetPath(eTexture::type texture)
	{
		switch (texture)
		{
		case eTexture::Player:    return "bird.png";
		case eTexture::Tileset:   return "tileset.png";
		case eTexture::BG:		  return "Green.png";
		case eTexture::Particles: return "particles.png";
		case eTexture::Light:	  return "light.png";
		case eTexture::health:	  return "health.png";
		case eTexture::enemy:	  return "enemy.png";
		case eTexture::flag:	  return "flag.png";
		case eTexture::gameover:  return "gameover.png";
		case eTexture::win:	      return "win.png";
		default:       return "UnknownTexType";
		}
	}

	class TextureManager
	{
	public:
		static TextureManager* GetInstance() { if (!sm_instance) sm_instance = new TextureManager(); return sm_instance; }
		~TextureManager();

		void LoadTextures();
		void UnLoadTextures();

		sf::Texture* GetTexture(eTexture::type texture) const { return m_textures[(int)texture]; }

	private:
		TextureManager();
		static TextureManager* sm_instance;

		sf::Texture* m_textures[eTexture::Count];
	};
}

namespace TextureHelper
{
	sf::Vector2f GetTextureTileSize(GameEngine::eTexture::type texture);
}


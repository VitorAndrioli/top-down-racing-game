#pragma once

#include <array>
#include <SFML\Graphics.hpp>

class TextureManager
{
private:
	static bool m_bInstanceFlag;
	static TextureManager *textureManager;
	TextureManager();
	void loadTextures();

	std::map< std::string, sf::Texture > m_textures;



public:
	static TextureManager* getInstance();
	~TextureManager();

	sf::Texture* getImage(const std::string name);
	//std::vector<sf::Texture> m_aTexture;
	

};


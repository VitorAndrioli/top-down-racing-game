#pragma once

#include <array>
#include <SFML\Graphics.hpp>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	void loadTextures();
	std::vector<sf::Texture> m_aTexture;
};


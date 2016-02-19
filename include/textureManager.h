#pragma once

#include <array>
#include <SFML\Graphics.hpp>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	void loadTextures();
	sf::Texture getImage(const std::string name);
	std::vector<sf::Texture> m_aTexture;
private:
	std::map< std::string, sf::Texture > images_;
};


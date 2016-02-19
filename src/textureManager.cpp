#include "textureManager.h"
#include <iostream>

using namespace std;

TextureManager::TextureManager()
{
}

void TextureManager::loadTextures()
{
	sf::Texture texture1, texture2, texture3, texture4, texture5, texture6, texture7, texture8;
	
	texture1.loadFromFile("assets/img/car_01.png");
	texture2.loadFromFile("assets/img/car_02.png");
	texture3.loadFromFile("assets/img/car_03.png");
	texture4.loadFromFile("assets/img/car_04.png");
	texture5.loadFromFile("assets/img/car_tyre.png");
	texture6.loadFromFile("assets/img/tyre.png");
	texture7.loadFromFile("assets/img/box.png");
	texture8.loadFromFile("assets/img/track_small.jpg");

	m_aTexture.push_back(texture1);
	m_aTexture.push_back(texture2);
	m_aTexture.push_back(texture3);
	m_aTexture.push_back(texture4);
	m_aTexture.push_back(texture5);
	m_aTexture.push_back(texture6);
	m_aTexture.push_back(texture7);
	m_aTexture.push_back(texture8);
}

sf::Texture TextureManager::getImage(const string name)
{
	for (std::map<std::string, sf::Texture>::const_iterator it = images_.begin();	it != images_.end(); ++it)
	{
		if (name == it->first)
		{
			return it->second;
		}
	}

	// The image doesen't exists. Create it and save it.
	sf::Texture texture;
	if (texture.loadFromFile(name))
	{
		images_[name] = texture;
		return images_[name];
	}

	images_[name] = texture;
	return images_[name];
}


TextureManager::~TextureManager()
{
	
}

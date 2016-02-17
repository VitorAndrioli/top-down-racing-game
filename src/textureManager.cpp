#include "textureManager.h"
#include <iostream>

TextureManager::TextureManager()
{
}

void TextureManager::loadTextures()
{
	sf::Texture texture1, texture2, texture3, texture4, texture5, texture6, texture7;
	texture1.loadFromFile("assets/img/car_01.png");
	texture2.loadFromFile("assets/img/car_02.png");
	texture3.loadFromFile("assets/img/car_03.png");
	texture4.loadFromFile("assets/img/car_04.png");
	texture5.loadFromFile("assets/img/car_tyre.png");
	texture6.loadFromFile("assets/img/tyre.png");
	texture7.loadFromFile("assets/img/box.png");

	
	m_aTexture.push_back(texture1);
	m_aTexture.push_back(texture2);
	m_aTexture.push_back(texture3);
	m_aTexture.push_back(texture4);
	m_aTexture.push_back(texture5);
	m_aTexture.push_back(texture6);
	m_aTexture.push_back(texture7);
}


TextureManager::~TextureManager()
{
	
}

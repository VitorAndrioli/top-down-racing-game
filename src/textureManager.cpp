#include "textureManager.h"

bool TextureManager::m_bInstanceFlag = false;
TextureManager* TextureManager::m_pTextureManager = nullptr;
TextureManager* TextureManager::getInstance()
{
	if (!m_bInstanceFlag)
	{
		m_pTextureManager = new TextureManager;
		m_bInstanceFlag = true;
	}
	return m_pTextureManager;
}

TextureManager::TextureManager()
{

}

shared_ptr<sf::Texture> TextureManager::getTexturePointer(const string name)
{
	string dir = "assets/img/";
	string extension = ".png";
	for (map< string, shared_ptr<sf::Texture> >::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
	{
		if (name == it->first)
		{
			return it->second;
		}
	}
	
	// The image doesen't exists. Create it and save it.
	shared_ptr<sf::Texture> texture(new sf::Texture);
	if (texture->loadFromFile(dir + name + extension))
	{
		m_textures[name] = texture;
		return m_textures[name];
	}
	
	m_textures[name] = texture;
	return m_textures[name];
}


TextureManager::~TextureManager()
{
	m_textures.clear();
}

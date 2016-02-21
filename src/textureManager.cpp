/*!
 * \file
 * \brief Implementation of TextureManager class.
 */

#include "textureManager.h"

// Initiates static variables.
bool TextureManager::m_bInstanceFlag = false;
TextureManager* TextureManager::m_pTextureManager = nullptr;

TextureManager::TextureManager()
{
}

/*!
 * \return Pointer to the texture manager instance.
 */
TextureManager* TextureManager::getInstance()
{
	// Checks if ans instance of TextureManager already exists.
	if (!m_bInstanceFlag)
	{
		// If not, creates one.
		m_pTextureManager = new TextureManager;
		m_bInstanceFlag = true;
	}
	return m_pTextureManager;
}

/*!
 * \param sName Name of the texture we wish to use.
 * \return Smart pointer to a texture.
 */
shared_ptr<sf::Texture> TextureManager::getTexturePointer(const string sName)
{
	string dir = "assets/img/"; // Images directory.
	string extension = ".png"; // Extension of images.

	// Looks in map for a texture associated with the name passed.
	for (map< string, shared_ptr<sf::Texture> >::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
	{
		// If there is one, return texture's shared pointer.
		if (sName == it->first)	return it->second;
	}
	
	// If the texture doesn't exists, try to load one and add it to the map.
	shared_ptr<sf::Texture> texture(new sf::Texture); // Blank texture to prevent runtime errors.
	if (texture->loadFromFile(dir + sName + extension))
	{
		m_textures[sName] = texture;
		return m_textures[sName];
	}
	
	// If no texture is found, save a blank texture instead.
	m_textures[sName] = texture;
	return m_textures[sName];
}


TextureManager::~TextureManager()
{
	m_textures.clear();
}

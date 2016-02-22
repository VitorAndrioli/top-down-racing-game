/*!
 * \file
 * \brief Declaration of TextureManager class.
 */

/*!
 * \class TextureManager textureManager.h "textureManager.h"
 * \brief Singleton for managing textures.
 *
 * Ensures that every image is loaded only once. Allows finding a pointer to a texture by a readable name.
 * Implements Singleton design pattern, so textures can be accessed across the software.
 *
 * \author Vitor Augusto Andrioli
 * \version 1.0
 * \date 25/02/2016
 */

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML\Graphics.hpp>
#include <memory>

using namespace std;

class TextureManager
{
public:
	static TextureManager* getInstance(); //!< Gets single instance of TextureManager.
	~TextureManager(); //!< Default destructor.
	shared_ptr<sf::Texture> getTexturePointer(const string sName); //!< Gets pointer to a texture by its name.

private:
	TextureManager(); //!< Private constructor.
	static bool m_bInstanceFlag; //!< Flag to make sure there is only one instance of TextureManager.
	static  TextureManager* m_pTextureManager; //!< Pointer to TextureManager instance.
	map< string, shared_ptr<sf::Texture> > m_textures; //!< Maps texture's name to its pointer.
};

#endif
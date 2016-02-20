//! \file textureManager.h Declaration of Box class.
/*!
* \class TextureManager
* \brief 
*/

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML\Graphics.hpp>
#include <memory>

using namespace std;

class TextureManager
{
private:
	TextureManager(); //!< Private constructor.
	static bool m_bInstanceFlag; //!< Flag to make sure there is only one instance of TextureManager.
	static  TextureManager *m_pTextureManager; //!< Pointer to TextureManager instance.
	map< string, shared_ptr<sf::Texture> > m_textures; //!< Maps texture's names to its pointer.

public:
	static TextureManager* getInstance(); //!< Gets single instance of TextureManager.
	~TextureManager(); //!< Basic destructor.
	shared_ptr<sf::Texture> getTexturePointer(const string name); //!< Gets pointer to a texture by its name.
};

#endif
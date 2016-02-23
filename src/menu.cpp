/*!
* \file
* \brief Implementation of Menu class.
*/

#include "menu.h"

Menu::Menu() : m_bMultiPlayer(false)
{
	// Gets instance of Singleton Texture Manager
	TextureManager* textureManager = TextureManager::getInstance();

	// Assigns and scale menu's texture.
	m_menuSprite.setTexture(*textureManager->getTexturePointer("menu"));
	m_menuSprite.setOrigin(m_menuSprite.getTexture()->getSize().x / 2, m_menuSprite.getTexture()->getSize().y / 2); // Sets sprite's center as its origin (instead of its corner).
	m_menuSprite.scale(450.f / m_menuSprite.getTexture()->getSize().x, 532.f / m_menuSprite.getTexture()->getSize().y); // Scales texture to make sure it fits the car.
	
	// Assigns and scale arrows's texture.
	m_arrowSprite.setTexture(*textureManager->getTexturePointer("arrow"));
	m_arrowSprite.setOrigin(m_arrowSprite.getTexture()->getSize().x / 2, m_arrowSprite.getTexture()->getSize().y / 4); // Sets sprite's center as its origin (instead of its corner).
	m_arrowSprite.scale(40.f / m_arrowSprite.getTexture()->getSize().x, 47.f / m_arrowSprite.getTexture()->getSize().y); // Scales texture to make sure it fits the car.

	m_buttonBuffer.loadFromFile("./assets/sounds/button.wav");
	m_buttonSound.setBuffer(m_buttonBuffer);
}

/*!
 * Changes game mode between single and multi player and moves selector arrow accordingly.
 */
void Menu::toggleOptions()
{
	// Toggle game mode option.
	m_bMultiPlayer = !m_bMultiPlayer;
	m_buttonSound.play();

	// Move arrow.
	if (m_bMultiPlayer)
	{
		m_arrowSprite.move(Vector2f(0, 62));
	}
	else
	{
		m_arrowSprite.move(Vector2f(0, -62));
	}
}

bool Menu::getOption()
{
	m_buttonSound.play();
	return m_bMultiPlayer;
}

void Menu::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(m_menuSprite);
	target.draw(m_arrowSprite);
}

void Menu::setSize(double x, double y)
{
	// Centers menu
	m_menuSprite.move(x / 2, y / 2);
	// Position arrow in Single Player position.
	m_arrowSprite.move((x / 2) - 140, (y / 2) + 15);
}

Menu::~Menu()
{
}

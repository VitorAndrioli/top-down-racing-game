/*!
 * \file
 * \brief Declaration of Menu class.
 */

/*!
 * \class Menu menu.h "menu.h"
 * \brief Displays a home screen with setting options for the user to choose from.
 *
 * User can choose between single and multi player options before starting the game.
 *
 * \author Vitor Augusto Andrioli
 * \version 1.0
 * \date 25/02/2016
 */

#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

#include "textureManager.h"

using namespace sf;

class Menu : public Drawable
{
public:
	Menu(); //!< Default contructor.
	~Menu(); //!< Default destructor.
	void setSize(double fWindowWidth, double fWindowHeight); //!< Set sprites sizes and position based on window's size.
	void toggleOptions(); //!< Changes between menu options.
	bool getOption(); //!< Gets selected option.

private:
	void draw(RenderTarget &target, RenderStates states) const; //!< Draw function (from sf::Drawable)
	bool m_bMultiPlayer; //!< If option selected is multi player.
	Sprite m_menuSprite; //!< Main menu sprite.
	Sprite m_arrowSprite; //!< Selector arrow sprite.
	sf::SoundBuffer m_buttonBuffer;
	sf::Sound m_buttonSound;

};

#endif
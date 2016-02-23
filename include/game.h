/*!
 * \file
 * \brief Declaration of Game class.
 */

/*!
 * \class Game game.h "game.h"
 * \brief Main game class.
 *
 * Instantiates every object in the game (cars, collidables, menus), updates and draws them.
 * Defines game mode (single or multi player) and controls user input.
 *
 * \author Vitor Augusto Andrioli
 * \version 1.0
 * \date 25/02/2016
 */

#ifndef GAME_H
#define GAME_H

#include "circle.h"
#include "collidable.h"
#include "collidableFactory.h"
#include "textureManager.h"
#include "car.h"
#include "carDisplay.h"
#include "tyre.h"
#include "box.h"
#include "vector2D.h"
#include "menu.h"
#include "rapidxml.hpp"
#include <array>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

using namespace sf;

class Game : public Drawable
{
public:
	Game(); //!< Default constructor
	void setMenuSize(const double fWidth, const double fHeight); //!< Defines menu size based in window's size.
	void setMode(); //!< Sets game mode (single or multi player).
	void load(); //!< Creates every object in the game.
	void update(float timestep); //!< Update all entities in the game.
	void processKeyPress(Keyboard::Key code); //!< Process any key presses.
	void processKeyRelease(Keyboard::Key code); //!< Process any key releases.
	
	bool isPaused(); //!< Check if game is paused.
	bool hasStarted(); //!< Check if game has started.
	bool isMultiplayer(); //!< Check if game is set to multiplayer.

	Vector2f getP1Position(); //!< Gets first player position.
	Vector2f getP2Position(); //!< Gets second player position, if multiplayer.
	CarDisplay* getP1Display(); //!< Gets pointer to first player velocimeter.
	CarDisplay* getP2Display(); //!< Gets pointer to second player velocimeter, if multiplayer.
	RectangleShape getInstructionsBackground();
	Text getInstructions();
	Text getTimer();
	
	
private:
	Car* player1; //!< Pointer to first player.
	Car* player2;  //!< Pointer to second player, if multi player mode is active.
	std::vector<Collidable*> m_pvCollidables; //!< Vector with pointers to every collidable object in the game.
	
	Font m_font; //!< Font used to write instructions
	Menu m_menu; //!< Main menu.
	RectangleShape m_instructionsBackground; //!< Background for instructions;
	Text m_instructions; //!< Instruction to be displayed when paused.
	Text m_timerText; //!< Timer to be draw into the screen.
	float m_fTimer; //!< Variable to store time elapsed of the game.
	char timerBuffer[100]; //!< Buffer to turn timer intp string.
	Sprite m_background; //!< Background of game (racing track).
	
	bool m_bMultiPlayer; //!< If game is defined as multi player.
	bool m_bStarted; //!< If game has started.
	bool m_bPaused; //!< If game is paused.

	void draw(RenderTarget &target, RenderStates states) const; //!< Draw function (from sf::Drawable)
};

#endif
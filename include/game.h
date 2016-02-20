//! \file game.h Declaration of Game class.

#ifndef GAME_H
#define GAME_H

#include "circle.h"
#include "collidable.h"
#include "collidableFactory.h"
#include "textureManager.h"
#include "car.h"
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
	Car* player1;
	Car* player2;
	bool m_bMultiPlayer;
	Menu m_menu;
	void setMenuSize(double x, double y);
	Sprite m_background;
	void setMode(bool mode);
	bool m_startGame;

	TextureManager *m_pTextureManager;
	//std::vector<std::shared_ptr<Collidable>> obstacles;
	std::vector<Collidable*> pObstacles;
	Game(); //!< Constructor
	void load();
	void draw(RenderTarget &target, RenderStates states) const; //!< Draw function (from sf::Drawable)
	void update(float timestep); //!< Update all entities in the game
	void processKeyPress(Keyboard::Key code); //!< Action any key presses
	void processKeyRelease(Keyboard::Key code); //!< Action any key releases
	View view1;
	bool m_bPaused;
	
};

#endif
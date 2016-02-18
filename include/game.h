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
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
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
	Car car;
	Tyre tyre;
	sf::Texture tyreTexture;
	sf::Texture carTexture;
	sf::Texture carTyreTexture;
	//std::array<Collidable*, 5> obstacles;
	TextureManager m_textureManager;
	std::vector<Collidable*> obstacles;
	Game(); //!< Constructor
	void draw(RenderTarget &target, RenderStates states) const; //!< Draw function (from sf::Drawable)
	void update(float timestep); //!< Update all entities in the game
	void processKeyPress(Keyboard::Key code); //!< Action any key presses
	void processKeyRelease(Keyboard::Key code); //!< Action any key releases
	View view1;
	bool m_bPaused;
	
};

#endif
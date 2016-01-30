/**
@file game.h
*/

#ifndef GAME_H
#define GAME_H

#include "circle.h"
#include "collidable.h"
#include "car.h"
#include "collision.h"
#include "vector2D.h"
#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>

using namespace sf;

class Game : public Drawable
{
public:
	Car car;
	//std::array<Collidable*, 5> obstacles;
	std::vector<Collidable*> obstacles;
	Game(); //!< Constructor
	void draw(RenderTarget &target, RenderStates states) const; //!< Draw function (from sf::Drawable)
	void update(float timestep); //!< Update all entities in the game
	void processKeyPress(Keyboard::Key code); //!< Action any key presses
	void processKeyRelease(Keyboard::Key code); //!< Action any key releases
	
};

#endif
/*!
* \file
* \brief Declaration of Circle class.
*/

/*!
 * \class Circle circle.h "circle.h"
 * \brief Circular collidables to be used in the game.
 *
 * Implements collision detection and texture allocation for circular objects.
 * Can be used to turn background figures into immovable collidables. 
 * A circle instance is not drawn to the screen.
 *
 * \author Vitor Augusto Andrioli
 * \version 1.0
 * \date 25/02/2016
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include "collidable.h"
#include "obb.h"

using namespace std;

class Circle : public Collidable
{
public:
	Circle(); //!< Basic constructor.
	//! Constructor initializing the position, radius and restitution coefficient.
	Circle(double fPosX, double fPosY, double fRadius, double fRestitution = 1);
	void checkCollision(Collidable* const pCollidable); //!< Checks collision with another Collidable.
	void checkCollision(Circle* const pOtherCircle); //!< Checks collision with another Circle.
	void checkCollision(OBB* const pObb); //!< Checks collision with an OBB.
	void setTexture(shared_ptr<sf::Texture> pTexture);

	void updatePoints(); //!< to be removed.
};

#endif
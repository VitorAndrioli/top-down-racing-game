//! \file circle.h Declaration of Circle class.
/*!
 * \class Circle
 *
 * \brief Circular collidables to be used in the game.
 *
 * Implements collision detection and texture allocation for circular objects.
 * Can be used to turn background figures into immovable collidables. A circle instance is not drawn to the screen.
 *
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include "collidable.h"
#include "obb.h"

class Circle : public Collidable
{
public:
	Circle(); //!< Basic constructor.
	//! Constructor initializing the position, radius and restitution coefficient with paramenters.
	Circle(double fPosX, double fPosY, double fRadius, double fRestitution = 1);
	void checkCollision(Collidable * pCollidable); //!< Checks collision with another Collidable.
	void checkCollision(Circle * pOtherCircle); //!< Checks collision with another Circle.
	void checkCollision(OBB * pObb); //!< Checks collision with an OBB.
	void setTexture(sf::Texture * texture);  //!< Assigns a texture to the object's sprite.

	void updatePoints(); //!< to be removed.

};

#endif
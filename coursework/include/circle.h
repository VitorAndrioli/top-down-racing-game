//! \file circle.h Declaration of Circle class.
/*!
 * \class Circle
 *
 * \brief Create circular collidables to be used in the game.
 *
 * Implements collision detection and texture allocation for circular objects.
 * Can be used to turn background figures into immovable collidables.
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
	//! Constructor that receives the position, radius and, optionally, the orientation of the object.
	Circle(double fPosX, double fPosY, double fRadius, double fOrientation = 0);
	void updatePoints(); //!< to be removed.
	void checkCollision(Collidable * collidable); //!< Check collision with another Collidable.
	void checkCollision(Circle * circle); //!< Check collision with another Circle.
	void checkCollision(OBB * obb); //!< Check collision with an OBB.
	void setTexture(sf::Texture * texture);  //!<
};

#endif
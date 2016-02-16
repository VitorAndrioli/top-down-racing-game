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
	void updatePoints(); //!< to be removed.
	void checkCollision(Collidable * pCollidable); //!< Check collision with another Collidable.
	void checkCollision(Circle * pOtherCircle); //!< Check collision with another Circle.
	void checkCollision(OBB * pObb); //!< Check collision with an OBB.
	void setTexture(sf::Texture * texture);  //!<
};

#endif
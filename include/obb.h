//! \file obb.h Declaration of OBB class.
/*!
 * \class OBB
 *
 * \brief Oriented Bounding Box (OBB) collidables to be used in the game.
 *
 * Implements collision detection and texture allocation for OBB objects.
 * Can be used to turn background figures into immovable collidables. An OBB instance is not drawn to the screen.
 *
 */

#ifndef OBB_H
#define OBB_H

#include "collidable.h"

class OBB : public Collidable
{
protected:
	Vector2D<double> m_fvHalfExtents; //!< Half-extents vector.
public:
	OBB(); //!< Basic constructor.
	//! Constructor receiving the position, half extents, orientation and restitution coefficient of box.
	OBB(double fPosX, double fPosY, double fHalfExtentX, double fHalfExtentY, double fOrientation, double fRestitution = 1);
	void checkCollision(Collidable * pCollidable); //!< Checks collision with another Collidable.
	void checkCollision(Circle * pCircle); //!< Checks collision with an Circle.
	void checkCollision(OBB * pOtherObb); //!< Checks collision with another OBB.
	
	// Setters and Getters.
	void setHalfExtents(double fHalfExtentX, double fHalfExtentY); //!< Sets X and Y values of half-extents vector and update object`s radius.
	Vector2D<double> getHalfExtents();
	void setTexture(sf::Texture * texture); //!< Assigns a texture to the object's sprite.


	void updatePoints(); // remove

};

#endif
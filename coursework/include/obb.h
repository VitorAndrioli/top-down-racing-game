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
	//! Constructor initializing the position, half extents, orientation and restitution coefficient with paramenters.
	OBB(double fPosX, double fPosY, double fHalfExtentX, double fHalfExtentY, double fOrientation, double fRestitution = 1);
	void updatePoints(); // remove
	void checkCollision(Collidable * pCollidable); //!< Check collision with another Collidable.
	void checkCollision(Circle * pCircle); //!< Check collision with an Circle.
	void checkCollision(OBB * pOtherObb); //!< Check collision with another OBB.
	void setTexture(sf::Texture * texture);
	
	// Basic getters and setters.
	Vector2D<double> getHalfExtents();
	void setHalfExtents(Vector2D<double>);
};

#endif
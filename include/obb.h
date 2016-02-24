/*!
* \file
* \brief Declaration of OBB class.
*/

/*!
 * \class OBB obb.h "obb.h"
 * \brief Oriented bounding box collidables to be used in the game.
 *
 * Implements collision detection and texture allocation for OBB objects.
 * Can be used to turn background figures into immovable collidables. 
 * An OBB instance is not drawn to the screen.
 *
 * \author Vitor Augusto Andrioli
 * \version 1.0
 * \date 25/02/2016
 */

#ifndef OBB_H
#define OBB_H

#include "collidable.h"
#include "circle.h"

using namespace std;

class OBB : public Collidable
{
public:
	OBB(); //!< Default constructor.
	
	//! Constructor initializing position, half extents, orientation and restitution coefficient.
	OBB(double fPosX, double fPosY, double fHalfExtentX, double fHalfExtentY, double fOrientation, double fRestitution = 1);
	void checkCollision(Collidable* const pCollidable); //!< Checks collision with another Collidable.
	void checkCollision(Circle* const pCircle); //!< Checks collision with an Circle.
	void checkCollision(OBB* const pOtherObb); //!< Checks collision with another OBB.
	
	// Setters and Getters.
	void setHalfExtents(double fHalfExtentX, double fHalfExtentY); //!< Sets X and Y values of half-extents vector and update object`s radius.
	Vector2D<double> getHalfExtents();
	void setTexture(shared_ptr<sf::Texture> pTexture); //!< Implements Collidable's setTexture virtual method.

protected:
	Vector2D<double> m_fvHalfExtents; //!< Half-extents vector.
};

#endif
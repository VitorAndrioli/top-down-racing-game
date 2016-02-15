/*!
 * \file box.h
 * \class Box
 *
 * \brief Create boxes to be used as collidable obstacles in the game.
 *
 */

#include "box.h"

/*! Initialize the necessary member variables with the position, size and (optionally) the orientation received as parameters 
 * and the default values for box objects.
 *
 * \param fPosX,fPosY Coordinates for the position vector.
 * \param fSize Size of the box. It is always a square.
 * \param fOrientation Orientation of the box. If no value is passed, it will be set to zero.
 *
 */
Box::Box(double fPosX, double fPosY, double fSize, double fOrientation = 0)
{
	// Assign paramenters to respective member variables.
	m_fvPosition.setX(fPosX); m_fvPosition.setY(fPosY);
	m_fvHalfExtents.setX(fSize); m_fvHalfExtents.setY(fSize);
	m_fOrientation = fOrientation;
	// Assign default values
	m_fFrictionCoefficient = BOX_FRICTION_COEFFICIENT;
	m_fRestitution = BOX_RESTITUTION_COEFFICIENT;
	setMass(BOX_MASS); // Use set method to save inverse of mass.
	
}


Box::Box()
{
}

Box::~Box()
{
}

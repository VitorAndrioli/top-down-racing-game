//! \file tyre.cpp Implementation of Tyre class.

#include "tyre.h"

Tyre::Tyre()
{
}

/*! Initialize the position with parameters and other member variables with the default values for tyre objects.
 *
 * \param fPosX,fPosY Coordinates for the position vector.
 *
 */
Tyre::Tyre(double fPosX, double fPosY)
{
	// Assign coordinates to position vector
	m_fvPosition.setX(fPosX); m_fvPosition.setY(fPosY); 
	// Assign default values
	m_fRadius = TYRE_RADIUS;
	m_fFrictionCoefficient = TYRE_FRICTION_COEFFICIENT;
	m_fRestitution = TYRE_RESTITUTION_COEFFICIENT;
	setMass(TYRE_MASS); // Use set method to save inverse of mass.
	m_fOrientation = 0; // As a circular collidable, the initial orientation is not relevant.
}

Tyre::~Tyre()
{
}

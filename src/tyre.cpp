//! \file tyre.cpp Implementation of Tyre class.

#include "tyre.h"

Tyre::Tyre()
{
}

/*! Initializes the position with parameters and other member variables with the default values for tyre objects.
 *
 * \param fPosX,fPosY Coordinates for the position vector.
 *
 */
Tyre::Tyre(double fPosX, double fPosY)
{
	// Assigns coordinates to position vector
	m_fvPosition.setX(fPosX); m_fvPosition.setY(fPosY); 
	// Assigns default values
	m_fRadius = TYRE_RADIUS;
	m_fFrictionCoefficient = TYRE_FRICTION_COEFFICIENT;
	m_fRestitution = TYRE_RESTITUTION_COEFFICIENT;
	setMass(TYRE_MASS); // Uses set method to save inverse of mass.
	m_fOrientation = 0; // As a circular collidable, the initial orientation is irrelevant.
	m_fInverseMomentOfInertia = 4 / (getMass()*pow(getRadius(), 4)); // Equation for moment of inertia for circles.
}

Tyre::~Tyre()
{
}

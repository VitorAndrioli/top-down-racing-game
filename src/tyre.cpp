/*!
 * \file
 * \brief Implementation of Tyre class.
 */

#include "tyre.h"

Tyre::Tyre()
{
}

/*! Initializes the position with parameters 
 * and assign default values to other member variables.
 *
 * \param fPosX,fPosY Coordinates for the position vector.
 */
Tyre::Tyre(double fPosX, double fPosY)
{
	// Assigns coordinates to position vector
	setPosition(fPosX, fPosY);
	// Assigns default values
	m_fRadius = TYRE_RADIUS;
	m_fFrictionCoefficient = TYRE_FRICTION_COEFFICIENT;
	m_fRestitution = TYRE_RESTITUTION_COEFFICIENT;
	setMass(TYRE_MASS); // Uses set method to save inverse of mass.
	m_fOrientation = 0; // Initial orientation is irrelevant for tyres.
	m_fInverseMomentOfInertia = 4 / (getMass()*pow(getRadius(), 4)); // Equation for moment of inertia for circles.
}

Tyre::~Tyre()
{
}

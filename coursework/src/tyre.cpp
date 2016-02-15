/*!
* \file tyre.h
* \class Tyre
*
* \brief Create tyres to be used as collidable obstacles in the game.
*
*/

#include "tyre.h"

//!< Initialize the necessary variables with the position received as a parameter and the default values for tyre objects.
Tyre::Tyre(double fPosX, double fPosY)
{
	m_fvPosition.setX(fPosX); m_fvPosition.setY(fPosY); //!< Assign parameters to position vector
	m_fRadius = TYRE_RADIUS;
	m_fFrictionCoefficient = TYRE_FRICTION_COEFFICIENT;
	m_fRestitution = TYRE_RESTITUTION_COEFFICIENT;
	setMass(TYRE_MASS); //!< Use set method to save inverse of mass.
	m_fOrientation = 0;

}

Tyre::Tyre()
{
}

Tyre::~Tyre()
{
}

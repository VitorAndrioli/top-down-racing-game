//! \file box.cpp Implementation of Box class.

#include "box.h"

Box::Box()
{
}

/*! Initialize the necessary the position, size and orientation with parameters received
 * and other member variables with the default values for box objects.
 * The orientation can be omitted in the instantiation of the object.
 *
 * \param fPosX,fPosY Coordinates for the position vector.
 * \param fSize Size of the box. It is always a square.
 * \param fOrientation Orientation of the box. If no value is passed, it will be set to zero.
 *
 */
Box::Box(double fPosX, double fPosY, double fSize, double fOrientation)
{
	// Assign paramenters to respective member variables.
	m_fvPosition.setX(fPosX); m_fvPosition.setY(fPosY);
	m_fvHalfExtents.setX(fSize); m_fvHalfExtents.setY(fSize);
	m_fRadius = m_fvHalfExtents.magnitude();
	m_fOrientation = fOrientation;
	// Assign default values
	m_fFrictionCoefficient = BOX_FRICTION_COEFFICIENT;
	m_fRestitution = BOX_RESTITUTION_COEFFICIENT;
	setMass(BOX_MASS_COEFFICIENT*fSize*fSize); // Use set method to save inverse of mass.
	m_fInverseMomentOfInertia = 12 / (getMass() * (fSize*fSize + fSize*fSize)); // Equation for moment of inertia for rectangles.
}

Box::~Box()
{
}

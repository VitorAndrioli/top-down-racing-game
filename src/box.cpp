/*!
 * \file
 * \brief Implementation of Box class.
 */

#include "box.h"

Box::Box()
{
}

/*! 
 * Initializes position, size and orientation with parameters 
 * and assign default values to other member variables.
 * The orientation can be omitted in the instantiation of the object and, in this case, will be set to zero.
 *
 * \param fPosX,fPosY Coordinates for the position vector.
 * \param fSize Size of the box. It is always a square.
 * \param fOrientation (Optional) Orientation of the box. If omitted, it will be set to zero.
 */
Box::Box(double fPosX, double fPosY, double fSize, double fOrientation)
{
	// Assigns paramenters to respective member variables.
	setPosition(fPosX, fPosY);
	setHalfExtents(fSize, fSize); // Uses setter method to set half-extents and radius.
	m_fOrientation = fOrientation;
	// Assigns default values
	m_fFrictionCoefficient = BOX_FRICTION_COEFFICIENT;
	m_fRestitution = BOX_RESTITUTION_COEFFICIENT;
	setMass(30 + BOX_MASS_COEFFICIENT*fSize*fSize); // Usse set method to save inverse of mass.
	m_fInverseMomentOfInertia = 1.f/500.f; // 12 / (getMass() * (fSize*fSize + fSize*fSize)); // Equation for moment of inertia for rectangles.
}

Box::~Box()
{
}

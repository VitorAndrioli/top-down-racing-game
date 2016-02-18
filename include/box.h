//! \file box.h Declaration of Box class.
/*!
 * \class Box
 * \brief Box to be used as collidable obstacle in the game.
 */

#ifndef BOX_H
#define BOX_H

#include "obb.h"

/*!
 */

// Definition of constant values to be assigned for box objects.
#define BOX_MASS_COEFFICIENT 2.0 //!< Default mass for box objects.
#define BOX_FRICTION_COEFFICIENT 0.68 //!< Default friction coefficient for box objects.
#define BOX_RESTITUTION_COEFFICIENT 0 //!< Default restitution coefficient for box objects.

class Box : public OBB
{
public:
	Box(); //!< Basic constructor. Does not initialize any member variable.
	//! Constructor receiving object's position, size and orientation.
	Box(double fPosX, double fPosY, double fSize, double fOrientation = 0);
	~Box(); //!< Basic destructor.
};

#endif
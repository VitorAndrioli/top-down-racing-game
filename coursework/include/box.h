/*!
 * \file box.h
 * \class Box
 *
 * \brief Create boxes to be used as collidable obstacles in the game.
 *
 */

#ifndef BOX_H
#define BOX_H

#include "obb.h"

// Define constant values to be assigned for box objects.
#define BOX_MASS 20.0 //!< Default mass for box objects.
#define BOX_FRICTION_COEFFICIENT 0.68 //!< Default friction coefficient for box objects.
#define BOX_RESTITUTION_COEFFICIENT 0.7 //!< Default restitution coefficient for box objects.

class Box : public OBB
{
public:
	//! Constructor that uses paramenters to iniatilize object's position, size and (optionally) orientation.
	Box(double fPosX, double fPosY, double fSize, double fOrientation = 0);
	Box(); //!< Basic constructor. Does not initialize any member variable.
	~Box(); //!< Basic destructor.
};

#endif
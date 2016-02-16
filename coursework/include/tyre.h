//! \file tyre.h Declaration of Tyre class.
/*!
 * \class Tyre
 * \brief Tyre to be used as collidable obstacle in the game.
 */

#ifndef TYRE_H
#define TYRE_H

#include "circle.h"

// Define constant values to be assigned for tyre objects.
#define TYRE_RADIUS 10.0 //!< Default radius for tyre objects.
#define TYRE_MASS 20.0 //!< Default mass for tyre objects.
#define TYRE_FRICTION_COEFFICIENT 0.68 //!< Default friction coefficient for tyre objects.
#define TYRE_RESTITUTION_COEFFICIENT 0.7 //!< Default restitution coefficient for tyre objects.

class Tyre : public Circle
{
public:
	Tyre(); //!< Basic constructor. Does not initialize any member variable.
	Tyre(double fPosX, double fPosY); //!< Constructor initializing position with paramenters received.
	~Tyre(); //!< Basic destructor
};

#endif
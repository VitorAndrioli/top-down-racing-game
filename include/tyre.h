/*!
* \file
* \brief Declaration of Tyre class.
*/

/*!
 * \class Tyre tyre.h "tyre.h"
 * \brief Collidable object to be used in the game.
 *
 * All tyres have the same size and mass.
 * The same texture is drawn to the screen.
 *
 * \author Vitor Augusto Andrioli
 * \version 1.0
 * \date 25/02/2016
 */

#ifndef TYRE_H
#define TYRE_H

#include "circle.h"

// Define constant values to be assigned for tyre objects.
#define TYRE_RADIUS 14.0 //!< Default radius for tyre objects.
#define TYRE_MASS 120.0 //!< Default mass for tyre objects.
#define TYRE_FRICTION_COEFFICIENT 0.68 //!< Default friction coefficient for tyre objects.
#define TYRE_RESTITUTION_COEFFICIENT 0.7 //!< Default restitution coefficient for tyre objects.

class Tyre : public Circle
{
public:
	Tyre(); //!< Default constructor.
	Tyre(double fPosX, double fPosY); //!< Constructor initializing position.
	~Tyre(); //!< Default destructor
};

#endif
/*! 
 * \file 
 * \brief Declaration of Box class.
 */

/*!
 * \class Box box.h "box.h"
 * \brief Collidable object to be used in the game.
 * 
 * Boxes can have different squared sizes. Its mass is based on its area.
 * The same texture (albeit sacaled) is draw to the screen for every instance.
 *
 * \author Vitor Augusto Andrioli
 * \version 1.0 
 * \date 25/02/2016
 */

#ifndef BOX_H
#define BOX_H

#include "obb.h"

// Definition of constant values to be assigned for box objects.
#define BOX_MASS_COEFFICIENT 0.4 //!< Default coefficient to define mass based on the its size.
#define BOX_FRICTION_COEFFICIENT 0.5 //!< Default friction coefficient for boxes.
#define BOX_RESTITUTION_COEFFICIENT 0.5 //!< Default restitution coefficient for boxes.

class Box : public OBB
{
public:
	Box(); //!< Default constructor.
	Box(double fPosX, double fPosY, double fSize, double fOrientation = 0); //!< Constructor initializing position, size and orientation.
	~Box(); //!< Default destructor.
};

#endif
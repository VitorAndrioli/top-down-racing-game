/*!
 * \file
 * \brief Declaration of CarDisplay class.
 */

/*!
 * \class CarDisplay carDisplay.h "carDisplay.h"
 * \brief Displays velocity of a Car instance as an analog speedometer.
 *
 * Uses car maximum speed and current speed to show the current velocity to the player.
 *
 * \author Vitor Augusto Andrioli
 * \version 1.0
 * \date 25/02/2016
 */

#ifndef CAR_DISPLAY_H
#define CAR_DISPLAY_H

#include <SFML\Graphics.hpp>
#include "textureManager.h"
#include <iostream>

#define MINIMUM_ROTATION 0 //!< Minimum rotation of the pointer, in degrees.
#define MAXIMUM_ROTATION 225 //!< Maximum rotation of the pointer, in degrees.

class CarDisplay : public sf::Drawable
{
public:
	CarDisplay(); //!< Default constructor
	CarDisplay(double fMaximumVelocity); //!< Constructor initializing the maximum velocity displayed.
	~CarDisplay(); //!< Default destructor.
	void update(double fSpeedSquared); //!< Updates pointer's orientation.

private:
	sf::Sprite m_speedometer; //!< Speedometer sprite.
	sf::Sprite m_speedometerPointer; //!< Pointer sprite.
	double m_fMaximumSpeedSquared; //!< Maximum speed the car can achieve. Use squared value to avoid using sqrt() function.
	void draw(sf::RenderTarget& target, sf::RenderStates states) const; //!< Virtual draw method inherited from Drawable class.
};

#endif
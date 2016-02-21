#pragma once

#define MINIMUM_ROTATION 0
#define MAXIMUM_ROTATION 225 // DEGREES

#include <SFML\Graphics.hpp>
#include "textureManager.h"
#include <iostream>

class CarDisplay : public sf::Drawable
{
public:
	CarDisplay();
	CarDisplay(double fMaximumVelocity);
	~CarDisplay();
	void update(double fSpeedSquared);

private:
	sf::Sprite m_velocimeter;
	sf::Sprite m_velocimeterPointer;
	sf::Sprite m_fuel;
	sf::Sprite m_fuelPointer;
	double m_fMaximumSpeedSquared;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const; //!< Virtual draw method inherited from Drawable class.


};


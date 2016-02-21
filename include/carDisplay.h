#pragma once

#include <SFML\Graphics.hpp>
#include "textureManager.h"

class CarDisplay : public sf::Drawable
{
public:
	CarDisplay();
	~CarDisplay();
	void update(double fElapsed);

private:
	sf::Sprite m_velocimeter;
	sf::Sprite m_velocimeterPointer;
	sf::Sprite m_fuel;
	sf::Sprite m_fuelPointer;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const; //!< Virtual draw method inherited from Drawable class.


};


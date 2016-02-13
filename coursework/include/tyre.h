#pragma once

#include <SFML\Graphics.hpp>
#include "circle.h"

class Tyre : public Circle
{
public:
	Tyre(double fPosX, double fPosY, double fOrientation, sf::Texture& texture);
	Tyre();
	~Tyre();
};


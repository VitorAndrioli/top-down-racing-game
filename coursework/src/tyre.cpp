#include "tyre.h"
#include "vector2D.h"


Tyre::Tyre(double fPosX, double fPosY, double fOrientation, sf::Texture& texture)
{
	m_fvPosition = Vector2D<double>(fPosX, fPosY);
	m_fRadius = 25;
	m_fOrientation = fOrientation;
	m_fInverseMass = 1.0 / (25.0 * 2.0);
	
	sf::Texture carTexture;
	carTexture.loadFromFile("assets/img/tyre.jpg");
	setTexture(&carTexture);
}

Tyre::Tyre()
{
}

Tyre::~Tyre()
{
}

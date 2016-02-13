#include "tyre.h"
#include "vector2D.h"


Tyre::Tyre(double fPosX, double fPosY, double fOrientation, sf::Texture& texture)
{
	m_fvPosition = Vector2D<double>(fPosX, fPosY);
	m_fRadius = 25;
	m_fOrientation = fOrientation;
	m_fInverseMass = 1.0 / (25.0 * 2.0);
	
	m_sprite.setTexture(texture);
	m_sprite.setOrigin(getRadius(), getRadius());
	m_sprite.setTextureRect(sf::IntRect(0, 0, getRadius() * 2, getRadius() * 2));
	m_sprite.scale(1, 1);
	m_sprite.setColor(sf::Color(255, 255, 255, 128));
	m_sprite.setPosition(getPosition().getX(), getPosition().getY());
	
}

Tyre::Tyre()
{
}

Tyre::~Tyre()
{
}

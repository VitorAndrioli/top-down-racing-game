#include "collidable.h"


Collidable::Collidable()
{
}

void Collidable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_vaPoints, states);
}

Vector<double> Collidable::getPosition()
{
	return m_dvPosition;
}
Vector<double> Collidable::getVelocity()
{
	return m_dvVelocity;
}
Vector<double> Collidable::getAcceleration()
{
	return m_dvAceleration;
}
double Collidable::getInverseMass()
{
	return m_dInverseMass;
}
double Collidable::getAngle()
{
	return m_dAngle;
}

void Collidable::setPosition(Vector<double> newPosition)
{
	m_dvPosition = newPosition;
}
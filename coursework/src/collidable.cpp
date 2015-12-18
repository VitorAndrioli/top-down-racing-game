#include "collidable.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

Collidable::Collidable()
{
}

void Collidable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_vaPoints, states);
}

void Collidable::setPosition(Vector<double> position)
{
	m_dvPosition = position;
}

void Collidable::setVelocity(Vector<double> velocity)
{
	m_dvPosition = velocity;
}

void Collidable::accelerate() {
	m_dAcceleration = 80;
}

void Collidable::decelerate() {
	m_dAcceleration = -80;
}

void Collidable::turnRight()
{
	m_dAngle += (5 * M_PI / 180);
}

void Collidable::turnLeft()
{
	m_dAngle -= (5 * M_PI / 180);
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
	return m_dvAcceleration;
}
double Collidable::getInverseMass()
{
	return m_dInverseMass;
}
double Collidable::getAngle()
{
	return m_dAngle;
}
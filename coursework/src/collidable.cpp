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

void Collidable::setPosition(Vector2D<double> position)
{
	m_dvPosition = position;
}

void Collidable::setVelocity(Vector2D<double> velocity)
{
	m_dvVelocity = velocity;
}

void Collidable::accelerate() {
	m_dThrust = 100;
	m_dvThrust = Vector2D<double>(100, 0);
	
	m_dvThrust.rotate(m_dAngle);
}

void Collidable::decelerate() {
	m_dThrust = 0;
}

void Collidable::reverse() {
	m_dThrust = -100;
	
}

void Collidable::turnRight()
{
	m_dAngle += (5 * M_PI / 180);
}

void Collidable::turnLeft()
{
	m_dAngle -= (5 * M_PI / 180);
}

Vector2D<double> Collidable::getPosition()
{
	return m_dvPosition;
}
Vector2D<double> Collidable::getVelocity()
{
	return m_dvVelocity;
}
Vector2D<double> Collidable::getAcceleration()
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
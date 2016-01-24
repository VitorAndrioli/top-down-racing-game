#include "collidable.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

Collidable::Collidable()
{
	m_dvVelocity = Vector2D<double>(0, 0);
	m_dvAcceleration = Vector2D<double>(0, 0);
	m_dvThrust = Vector2D<double>(0, 0);

	m_vaPoints.setPrimitiveType(sf::LinesStrip);
}

void Collidable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_vaPoints, states);
}

void Collidable::update(float elapsed)
{

	Vector2D<double> oldVelocity = m_dvVelocity;
	double oldAngle = m_dAngle;

	Vector2D<double> maxVel(130, 0);
	Vector2D<double> minVel(0.1, 0.1);
	maxVel.rotate(m_dAngle);
	
	double mu = 0.4;
	Vector2D<double> friction = m_dvVelocity.multiplyScalar(mu);
	
	m_dvAcceleration = m_dvThrust.subtract(&friction);

	m_dvVelocity = m_dvVelocity.add(&m_dvAcceleration.multiplyScalar(elapsed));
	

	

	//std::cout << (m_dvPosition.unitVector()).dotProduct(&m_dvAcceleration.unitVector()) << std::endl;





	if (abs(m_dvVelocity.squaredMagnitude()) > maxVel.squaredMagnitude()) 
	{
		m_dvVelocity = maxVel;
	}

	if (abs(m_dvVelocity.squaredMagnitude()) < minVel.squaredMagnitude())
	{
		m_dvVelocity = Vector2D<double>(0, 0);
	}

	
	m_dvPosition = m_dvPosition.add(&m_dvVelocity.multiplyScalar(elapsed));

	

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
	m_dvThrust = Vector2D<double>(100, 0);
	
	m_dvThrust.rotate(m_dAngle);
}

void Collidable::decelerate() {
	m_dvThrust = Vector2D<double>(0, 0);
}

void Collidable::reverse() {
	m_dvThrust = Vector2D<double>(-100, 0);

	m_dvThrust.rotate(m_dAngle);
	
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
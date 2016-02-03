#include "collidable.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

Collidable::Collidable()
{
	m_fvVelocity = Vector2D<double>(0, 0);
	m_fvAcceleration = Vector2D<double>(0, 0);
	m_fvThrust = Vector2D<double>(0, 0);
	m_fFrictionCoef = 0.4;

	m_vaPoints.setPrimitiveType(sf::LinesStrip);
}

void Collidable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_vaPoints, states);
}

void Collidable::print()
{
	std::cout << m_fvPosition.getX() << " -- " << m_fvPosition.getY() << std::endl;
}

void Collidable::update(float elapsed)
{
	Vector2D<double> friction = m_fvVelocity.multiplyScalar(m_fFrictionCoef);
	
	m_fvAcceleration = m_fvThrust.subtract(&friction);
	m_fvVelocity = m_fvVelocity.add(&m_fvAcceleration.multiplyScalar(elapsed));
	m_fvPosition = m_fvPosition.add(&m_fvVelocity.multiplyScalar(elapsed));

	updatePoints();

}

void Collidable::resolveImpulse(Collidable * collidable, Vector2D<double> * collisionNormal)
{
	double e = 0.6;

	double j;

	Vector2D<double> va_vb;
	va_vb = getVelocity().subtract(&collidable->getVelocity());

	j = (-(1 + e) * va_vb.dotProduct(collisionNormal)) / (getInverseMass() + collidable->getInverseMass());

	Vector2D<double> newVa = getVelocity().add(&collisionNormal->multiplyScalar(j).divideScalar(1 / getInverseMass()));
	Vector2D<double> newVb = collidable->getVelocity().subtract(&collisionNormal->multiplyScalar(j).divideScalar(1 / collidable->getInverseMass()));

	setVelocity(newVa);
	collidable->setVelocity(newVb);

}

void Collidable::setPosition(Vector2D<double> position)
{
	m_fvPosition = position;
}

void Collidable::setVelocity(Vector2D<double> velocity)
{
	m_fvVelocity = velocity;
}

void Collidable::setAcceleration(Vector2D<double> acceleration)
{
	m_fvAcceleration = acceleration;
}

Vector2D<double> Collidable::getPosition()
{
	return m_fvPosition;
}
Vector2D<double> Collidable::getVelocity()
{
	return m_fvVelocity;
}
Vector2D<double> Collidable::getAcceleration()
{
	return m_fvAcceleration;
}
double Collidable::getInverseMass()
{
	return m_fInverseMass;
}
double Collidable::getAngle()
{
	return m_fAngle;
}
void Collidable::setAngle(double angle)
{
	m_fAngle = angle;
}
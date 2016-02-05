#include "collidable.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

Collidable::Collidable()
{
	setVelocity(Vector2D<double>(0, 0));
	setAcceleration(Vector2D<double>(0, 0));
	setThrust(Vector2D<double>(0, 0));
	setFrictionCoefficient(0.4);
	setElasticity(0.6);

	m_vaPoints.setPrimitiveType(sf::LinesStrip);
}

void Collidable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_vaPoints, states);
}

void Collidable::update(float elapsed)
{
	Vector2D<double> friction = m_fvVelocity * getFrictionCoefficient();
	
	setAcceleration(getThrust() - friction);
	m_fvVelocity += getAcceleration() * elapsed;
	m_fvPosition += getVelocity() * elapsed;

	updatePoints();
}

void Collidable::resolveImpulse(Collidable * collidable, Vector2D<double> * collisionNormal)
{
	double fElasticity = min(getElasticity(), collidable->getElasticity());
	
	Vector2D<double> vaMinusVb = getVelocity() - collidable->getVelocity();
	double j = -(1 + fElasticity) * vaMinusVb.dotProduct(collisionNormal) / (getInverseMass() + collidable->getInverseMass());

	setVelocity(getVelocity() + (*collisionNormal * j / getMass()));
	collidable->setVelocity(collidable->getVelocity() - (*collisionNormal * j / collidable->getMass()));
}


void Collidable::setPosition(Vector2D<double> position)
{
	m_fvPosition = position;
}
Vector2D<double> Collidable::getPosition()
{
	return m_fvPosition;
}

void Collidable::setVelocity(Vector2D<double> velocity)
{
	m_fvVelocity = velocity;
}
Vector2D<double> Collidable::getVelocity()
{
	return m_fvVelocity;
}

void Collidable::setAcceleration(Vector2D<double> acceleration)
{
	m_fvAcceleration = acceleration;
}
Vector2D<double> Collidable::getAcceleration()
{
	return m_fvAcceleration;
}

void Collidable::setThrust(Vector2D<double> fvThrust)
{
	m_fvThrust = fvThrust;
}
Vector2D<double> Collidable::getThrust()
{
	return m_fvThrust;
}

void Collidable::setMass(double fMass)
{
	m_fInverseMass = 1.0 / fMass;
}
double Collidable::getMass()
{
	return 1/m_fInverseMass;
}
double Collidable::getInverseMass()
{
	return m_fInverseMass;
}

void Collidable::setAngle(double angle)
{
	m_fAngle = angle;
}
double Collidable::getAngle()
{
	return m_fAngle;
}

void Collidable::setFrictionCoefficient(double fFrictionCoefficient)
{
	m_fFrictionCoefficient = fFrictionCoefficient;
}
double Collidable::getFrictionCoefficient()
{
	return m_fFrictionCoefficient;
}

void Collidable::setElasticity(double fRestitution)
{
	m_fElasticity = fRestitution;
}
double Collidable::getElasticity()
{
	return m_fElasticity;
}
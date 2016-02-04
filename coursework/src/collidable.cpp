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
	Vector2D<double> friction = m_fvVelocity.multiplyScalar(m_fFrictionCoefficient);
	
	m_fvAcceleration = m_fvThrust.subtract(&friction);
	m_fvVelocity = m_fvVelocity.add(&m_fvAcceleration.multiplyScalar(elapsed));
	m_fvPosition = m_fvPosition.add(&m_fvVelocity.multiplyScalar(elapsed));

	updatePoints();
}

void Collidable::resolveImpulse(Collidable * collidable, Vector2D<double> * collisionNormal)
{
	double fElasticity = min(getElasticity(), collidable->getElasticity());
	
	Vector2D<double> vaMinusVb = getVelocity().subtract(&collidable->getVelocity());
	double j = (-(1 + fElasticity) * vaMinusVb.dotProduct(collisionNormal)) / (getInverseMass() + collidable->getInverseMass());

	Vector2D<double> newVa = getVelocity().add(&collisionNormal->multiplyScalar(j).divideScalar(getMass()));
	Vector2D<double> newVb = collidable->getVelocity().subtract(&collisionNormal->multiplyScalar(j).divideScalar(collidable->getMass()));

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
double Collidable::getMass()
{
	return 1/m_fInverseMass;
}
void Collidable::setMass(double fMass)
{
	m_fInverseMass = 1.0 / fMass;
}
double Collidable::getAngle()
{
	return m_fAngle;// *180 / M_PI; // convert to degrees
}
void Collidable::setAngle(double angle)
{
	m_fAngle = angle * M_PI / 180; //converts to radians
}
double Collidable::getFrictionCoefficient()
{
	return m_fFrictionCoefficient;
}
void Collidable::setFrictionCoefficient(double fFrictionCoefficient)
{
	m_fFrictionCoefficient = fFrictionCoefficient;
}
double Collidable::getElasticity()
{
	return m_fElasticity;
}
void Collidable::setElasticity(double fRestitution)
{
	m_fElasticity = fRestitution;
}
void Collidable::setThrust(Vector2D<double> fvThrust)
{
	m_fvThrust = fvThrust;
}
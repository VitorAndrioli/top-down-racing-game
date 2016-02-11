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

	m_fAngularVelocity = 0;
	m_fTorque = 0;
	m_fInverseMomentOfInertia = 0;


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

	m_fAngularVelocity += m_fTorque * m_fInverseMomentOfInertia * elapsed;

	m_fvPosition += getVelocity() * elapsed;

	m_fAngle += m_fAngularVelocity * elapsed;

	updatePoints();
}

bool Collidable::broadCollisionCheck(Collidable * collidable)
{
	double fCentreDistSquared = (getPosition() - collidable->getPosition()).squaredMagnitude();
	double fRadiiSumSquared = (getRadius() + collidable->getRadius()) * (getRadius() + collidable->getRadius());

	if (fCentreDistSquared - fRadiiSumSquared <= 0) return true;
	else return false;
	
}

void Collidable::resolveCollision(Collidable * collidable, Vector2D<double> * collisionNormal, double overlap)
{
	collidable->setPosition(collidable->getPosition() + (*collisionNormal * overlap));
	
	double fElasticity = min(getElasticity(), collidable->getElasticity());
	
	Vector2D<double> relVelocity = getVelocity() - collidable->getVelocity();
	
	double velAlongNormal = relVelocity.dotProduct(collisionNormal);
	if (velAlongNormal > 0) return;

	double j = -(1 + fElasticity) * relVelocity.dotProduct(collisionNormal) / (getInverseMass() + collidable->getInverseMass());

	setVelocity(getVelocity() + (*collisionNormal * j / getMass()));
	collidable->setVelocity(collidable->getVelocity() - (*collisionNormal * j / collidable->getMass()));
}

bool Collidable::isMoving()
{
	return getVelocity().squaredMagnitude() > 0;
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
	if (abs(m_fvVelocity.squaredMagnitude()) < 5) m_fvVelocity = Vector2D<double>(0, 0);
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
	if (fMass <= 0) m_fInverseMass = 0;
	else m_fInverseMass = 1.0 / fMass;
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




double Collidable::getRadius()
{
	return m_fRadius;
}
void Collidable::setRadius(double fRadius)
{
	if (fRadius >= 0)
		m_fRadius = fRadius;
	else
		m_fRadius = 1;
}


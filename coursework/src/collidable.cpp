/**
* \file collidable.cpp
*
*/

#include "collidable.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

Collidable::Collidable()
{
	m_fvVelocity = Vector2D<double>(0, 0);
	m_fvAcceleration = Vector2D<double>(0, 0);
	m_fvThrust = Vector2D<double>(0, 0);
	m_fFrictionCoefficient = 0.4;
	m_fRestitution = 0.6;

	m_fAngularVelocity = 0;
	m_fTorque = 0;
	m_fInverseMomentOfInertia = 0;


	m_vaPoints.setPrimitiveType(sf::LinesStrip);
}

void Collidable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
	target.draw(m_vaPoints, states);
}

void Collidable::update(float elapsed)
{
	Vector2D<double> friction = m_fvVelocity * m_fFrictionCoefficient;
	
	m_fvAcceleration = (m_fvThrust - friction);
	m_fvVelocity += m_fvAcceleration * elapsed;

	m_fAngularVelocity += m_fTorque * m_fInverseMomentOfInertia * elapsed;

	m_fvPosition += m_fvVelocity * elapsed;

	m_fOrientation += m_fAngularVelocity * elapsed;

	updateSprite();
	updatePoints();
}

void Collidable::updateSprite()
{
	m_sprite.setPosition(m_fvPosition.getX(), m_fvPosition.getY());
	m_sprite.setRotation(m_fOrientation * TO_DEGREES);

}

bool Collidable::broadCollisionCheck(Collidable * otherCollidable)
{
	double fCentreDistSquared = (m_fvPosition - otherCollidable->getPosition()).squaredMagnitude();
	double fRadiiSumSquared = (m_fRadius + otherCollidable->getRadius()) * (m_fRadius + otherCollidable->getRadius());

	if (fCentreDistSquared - fRadiiSumSquared <= 0) return true;
	return false;
	
}

void Collidable::resolveCollision(Collidable * otherCollidable, Vector2D<double> * fvCollisionNormal, double fOverlap)
{
	otherCollidable->setPosition(otherCollidable->getPosition() + (*fvCollisionNormal * fOverlap));
	
	double fRestitution = min(m_fRestitution, otherCollidable->getRestitution());
	
	Vector2D<double> relVelocity = m_fvVelocity - otherCollidable->getVelocity();
	
	double velAlongNormal = relVelocity.dotProduct(fvCollisionNormal);
	if (velAlongNormal > 0) return;

	double j = -(1 + fRestitution) * relVelocity.dotProduct(fvCollisionNormal) / (m_fInverseMass + otherCollidable->getInverseMass());

	m_fvVelocity += (*fvCollisionNormal * j * m_fInverseMass);
	otherCollidable->setVelocity(otherCollidable->getVelocity() - (*fvCollisionNormal * j * otherCollidable->getInverseMass()));
}

bool Collidable::isMoving()
{
	return m_fvVelocity.squaredMagnitude() > 0;
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
	if (abs(m_fvVelocity.squaredMagnitude()) < 0.05) m_fvVelocity = Vector2D<double>(0, 0);
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

void Collidable::setOrientation(double angle)
{
	m_fOrientation = angle;
}
double Collidable::getOrientation()
{
	return m_fOrientation;
}

void Collidable::setFrictionCoefficient(double fFrictionCoefficient)
{
	m_fFrictionCoefficient = fFrictionCoefficient;
}
double Collidable::getFrictionCoefficient()
{
	return m_fFrictionCoefficient;
}

void Collidable::setRestitution(double fRestitution)
{
	m_fRestitution = fRestitution;
}
double Collidable::getRestitution()
{
	return m_fRestitution;
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
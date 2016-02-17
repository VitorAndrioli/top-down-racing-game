//! \file collidable.cpp Implementation of Collidable class.

#include "collidable.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

//! Initialize all relevant variables to 0.
Collidable::Collidable()
{
	m_fvVelocity.setX(0); m_fvVelocity.setY(0);
	m_fvAcceleration.setX(0); m_fvAcceleration.setY(0);
	m_fvThrust.setX(0); m_fvThrust.setY(0);
	

	setMass(0);
	m_fOrientation = 0;
	m_fRadius = 1;
	m_fFrictionCoefficient = 0;
	m_fRestitution = 0;
	m_fAngularVelocity = 0;
	m_fAngularAcceleration = 0;
	m_fTorque = 0;
	m_fInverseMomentOfInertia = 0;


	m_vaPoints.setPrimitiveType(sf::LinesStrip); // to be removed.
}

//! Draw object sprite to target.
void Collidable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
	target.draw(m_vaPoints, states);
}

void Collidable::update(float elapsed)
{
	Vector2D<double> friction = m_fvVelocity * getFrictionCoefficient();
	
	//if (m_fInverseMass == 0) m_fvAcceleration = (m_fvThrust - friction);
	//else 
	m_fvAcceleration = (m_fvThrust - friction) * m_fInverseMass;

	m_fvVelocity += m_fvAcceleration * elapsed;
	m_fvPosition += m_fvVelocity * elapsed;

	double f = m_fAngularVelocity * m_fFrictionCoefficient;
	m_fAngularAcceleration = m_fTorque - f;//*m_fInverseMomentOfInertia;
	m_fAngularVelocity += m_fAngularAcceleration * elapsed;

	//cout << m_fTorque << " | " << m_fInverseMomentOfInertia << endl;

	if (m_fRadius < 20) cout << m_fOrientation << endl;

	m_fOrientation += m_fAngularVelocity * elapsed;

	updateSprite();
	updatePoints();
	m_fTorque = 0;
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

void Collidable::resolveCollision(Collidable * otherCollidable, Vector2D<double> * fvCollisionNormal, double fOverlap, Vector2D<double> * fvContactPoint)
{
	otherCollidable->setPosition(otherCollidable->getPosition() + (*fvCollisionNormal * fOverlap));

	double fRestitution = min(m_fRestitution, otherCollidable->getRestitution());

	Vector2D<double> relVelocity = m_fvVelocity - otherCollidable->getVelocity();

	double velAlongNormal = relVelocity.dotProduct(fvCollisionNormal);
	if (velAlongNormal > 0) return;

	Vector2D<double> ra = *fvContactPoint - m_fvPosition;
	Vector2D<double> rb = *fvContactPoint - otherCollidable->getPosition();

	Vector2D<double> relativeVelocity = (m_fvVelocity + ra.crossProduct(m_fAngularVelocity)) - (otherCollidable->getVelocity() + rb.crossProduct(otherCollidable->m_fAngularVelocity));

	
	double j = -(1 + fRestitution) * relativeVelocity.dotProduct(fvCollisionNormal) / (m_fInverseMass + otherCollidable->getInverseMass() + ra.crossProduct(fvCollisionNormal)*ra.crossProduct(fvCollisionNormal)*m_fInverseMomentOfInertia + rb.crossProduct(fvCollisionNormal)*rb.crossProduct(fvCollisionNormal)*otherCollidable->getInverseInertia());

	applyImpulse(j, fvCollisionNormal, &ra);
	otherCollidable->applyImpulse(-j, fvCollisionNormal, &rb);
}

void Collidable::applyImpulse(double fJ, Vector2D<double> * fvCollisionNormal, Vector2D<double> * fvContactPoint)
{
	m_fvVelocity += (*fvCollisionNormal * fJ * m_fInverseMass);
	m_fAngularVelocity += (*fvContactPoint).crossProduct(&(*fvCollisionNormal * fJ)) * m_fInverseMomentOfInertia;
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

double Collidable::getInverseInertia()
{
	return m_fInverseMomentOfInertia;
}
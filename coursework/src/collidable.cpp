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
	m_fElasticity = 0.6;

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
	Vector2D<double> friction = m_fvVelocity * m_fFrictionCoefficient;
	
	m_fvAcceleration = (m_fvThrust - friction) * m_fInverseMass;
	m_fvVelocity += m_fvAcceleration * elapsed;

	m_fAngularVelocity += m_fTorque * m_fInverseMomentOfInertia * elapsed;

	m_fvPosition += m_fvVelocity * elapsed;

	m_fOrientation += m_fAngularVelocity * elapsed;

	updatePoints();
}

bool Collidable::broadCollisionCheck(Collidable * collidable)
{
	double fCentreDistSquared = (m_fvPosition - collidable->getPosition()).squaredMagnitude();
	double fRadiiSumSquared = (m_fRadius + collidable->getRadius()) * (m_fRadius + collidable->getRadius());

	if (fCentreDistSquared - fRadiiSumSquared <= 0) return true;
	return false;
	
}

void Collidable::resolveCollision(Collidable * collidable, Vector2D<double> * collisionNormal, double overlap)
{
	collidable->setPosition(collidable->getPosition() + (*collisionNormal * overlap));
	
	double fElasticity = min(m_fElasticity, collidable->getElasticity());
	
	Vector2D<double> relVelocity = m_fvVelocity - collidable->getVelocity();
	
	double velAlongNormal = relVelocity.dotProduct(collisionNormal);
	if (velAlongNormal > 0) return;

	double j = -(1 + fElasticity) * relVelocity.dotProduct(collisionNormal) / (m_fInverseMass + collidable->getInverseMass());

	m_fvVelocity += (*collisionNormal * j * m_fInverseMass);
	collidable->setVelocity(collidable->getVelocity() - (*collisionNormal * j * collidable->getInverseMass()));
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


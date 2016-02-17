//! \file collidable.cpp Implementation of Collidable class.

#include "collidable.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

//! Initialize all relevant variables.
Collidable::Collidable()
{
	// Linear components
	m_fvVelocity.setX(0); m_fvVelocity.setY(0);
	m_fvAcceleration.setX(0); m_fvAcceleration.setY(0);
	m_fvThrust.setX(0); m_fvThrust.setY(0);
	setMass(0);
	
	// Angular components
	m_fOrientation = 0;
	m_fAngularVelocity = 0;
	m_fAngularAcceleration = 0;
	m_fTorque = 0;
	m_fInverseMomentOfInertia = 0;

	m_fRadius = 1;
	m_fFrictionCoefficient = 0;
	m_fRestitution = 1;



	m_vaPoints.setPrimitiveType(sf::LinesStrip); // to be removed.
}

/*!
 * Implements basic mechanics for movable objects (motion and forces),
 *
 * \param elapsed Time elapsed since last frame.
 */
void Collidable::update(float elapsed)
{
	// Calculates the friction of the object, based on the velocity.
	Vector2D<double> fvFriction = m_fvVelocity * getFrictionCoefficient();
	
	// Use F = m.a equation to calculate the acceleration of the object.
	m_fvAcceleration = (m_fvThrust - fvFriction) * m_fInverseMass;

	// Use Improved Euler to get the velocity and position of the object.
	Vector2D<double> fvPredictedVelocity = m_fvVelocity + m_fvAcceleration * elapsed;
	Vector2D<double> fvNewFriction = fvPredictedVelocity * getFrictionCoefficient();
	Vector2D<double> fvPredictedAcceleration = (m_fvThrust - fvNewFriction) * m_fInverseMass;
	
	setVelocity(m_fvVelocity + (m_fvAcceleration + fvPredictedAcceleration) * 0.5 * elapsed);
	m_fvPosition += m_fvVelocity * elapsed;;

	// Calculate angular components.
	double f = m_fAngularVelocity * m_fFrictionCoefficient;
	m_fAngularAcceleration = m_fTorque - f;//*m_fInverseMomentOfInertia;
	m_fAngularVelocity += m_fAngularAcceleration * elapsed;
	m_fOrientation += m_fAngularVelocity * elapsed;
	m_fTorque = 0;

	// Update sprite.
	updateSprite();
	updatePoints(); // to be removed
	
}


void Collidable::updateSprite()
{
	m_sprite.setPosition(m_fvPosition.getX(), m_fvPosition.getY());
	m_sprite.setRotation(m_fOrientation * TO_DEGREES);

}

/*!
 *	Use both collidable's radii to perform quicker collision detection testes before advancing to more costly methods.
 *
 * \param
 */
bool Collidable::broadCollisionCheck(Collidable * otherCollidable)
{
	double fCentreDistSquared = (m_fvPosition - otherCollidable->getPosition()).squaredMagnitude();
	double fRadiiSumSquared = (m_fRadius + otherCollidable->getRadius()) * (m_fRadius + otherCollidable->getRadius());

	if (fCentreDistSquared - fRadiiSumSquared <= 0) return true;
	return false;
	
}

/*!
*	\brief Resolve collision between two collidable objects.
*
*	Resolve overlap of two colliding objects, calculate and update their velocities.
*/
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

	
	//double j = -(1 + fRestitution) * relativeVelocity.dotProduct(fvCollisionNormal) / (m_fInverseMass + otherCollidable->getInverseMass() + (m_fInverseMomentOfInertia*pow(ra.crossProduct(fvCollisionNormal), 2)) + (otherCollidable->getInverseInertia() * pow(rb.crossProduct(fvCollisionNormal), 2)));
	double j = -(1 + fRestitution) * relVelocity.dotProduct(fvCollisionNormal) / (m_fInverseMass + otherCollidable->getInverseMass());
	

	applyImpulse(&(*fvCollisionNormal * j), &ra);
	otherCollidable->applyImpulse(&(*fvCollisionNormal * -j), &rb);
}

void Collidable::applyImpulse(Vector2D<double> * fvImpulse, Vector2D<double> * fvContactPoint)
{
	m_fvVelocity += (*fvImpulse * m_fInverseMass);
	//m_fAngularVelocity += (*fvContactPoint).crossProduct(fvImpulse) * m_fInverseMomentOfInertia;
}


bool Collidable::isMoving()
{
	return m_fvVelocity.squaredMagnitude() > 0;
}

/*!
* Draw object sprite to target.
*
* \param target Target to which draw the sprite.
* \param states States used for drawing to a RenderTarget.
*/
void Collidable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
	target.draw(m_vaPoints, states); // to remove.
}

// Setters and getters.
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
	cout << m_fvVelocity.squaredMagnitude() << endl;
	if (m_fvVelocity.squaredMagnitude() < 5) m_fvVelocity = Vector2D<double>(0, 0);
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
double Collidable::getInverseMass()
{
	return m_fInverseMass;
}

double Collidable::getMass()
{
	if (m_fInverseMass > 0)	return 1.f / m_fInverseMass;
	else return 0;
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
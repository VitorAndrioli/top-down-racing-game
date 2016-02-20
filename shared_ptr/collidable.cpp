//! \file collidable.cpp Implementation of Collidable class.

#include "collidable.h"
#include <iostream>

//! Initializes all relevant variables.
Collidable::Collidable() : 
	m_fvVelocity(0, 0), 
	m_fvAcceleration(0, 0), 
	m_fvThrust(0, 0), 
	m_fOrientation(0), 
	m_fInverseMass(0), 
	m_fAngularVelocity(0), 
	m_fAngularAcceleration(0), 
	m_fTorque(0), 
	m_fInverseMomentOfInertia(0),
	m_fRadius(1),
	m_fFrictionCoefficient(0), 
	m_fRestitution(1)
{
	m_vaPoints.setPrimitiveType(sf::LinesStrip); // to be removed.
}

/*!
 * Implements basic mechanics for movable objects (motion and forces).
 *
 * \param elapsed Time elapsed since last frame.
 */
void Collidable::update(float fElapsed)
{
	// Calculates the friction of the object, based on the velocity.
	Vector2D<double> fvFriction(5.5 * getMass(), 0);
	fvFriction.rotate(m_fvVelocity.getOrientation());

	Vector2D<double> fvAirFriction = (m_fvVelocity * getFrictionCoefficient());
	// Uses F = m.a equation to calculate the acceleration of the object.
	m_fvAcceleration = (m_fvThrust - fvAirFriction) *m_fInverseMass;

	if (isMoving()) m_fvAcceleration -= fvFriction;
	
	//cout << m_fvAcceleration.magnitude() << endl;

	// Uses Improved Euler to get the velocity and position of the object.
	Vector2D<double> fvPredictedVelocity = m_fvVelocity + m_fvAcceleration * fElapsed;
	Vector2D<double> fvNewFriction = fvPredictedVelocity * getFrictionCoefficient();
	Vector2D<double> fvPredictedAcceleration = (m_fvThrust - fvNewFriction) * m_fInverseMass;
	
	setVelocity(m_fvVelocity + (m_fvAcceleration + fvPredictedAcceleration) * 0.5 * fElapsed);
	m_fvPosition += m_fvVelocity * fElapsed;;

	
	// Calculates angular components.
	double airFriction = m_fAngularVelocity * 1;
	double friction = 0.1 * getMass();
	if (airFriction < 0) friction *= -1;

	m_fAngularAcceleration = (m_fTorque - airFriction) * m_fInverseMass;
	
	if (isRotating()) m_fAngularAcceleration = m_fAngularAcceleration - friction;
	
	m_fAngularVelocity += m_fAngularAcceleration * fElapsed;
	m_fOrientation += m_fAngularVelocity * fElapsed;
	
	// Updates sprite.
	updateSprite();
	updatePoints(); // to be removed

	if (abs(m_fAngularVelocity) < 1) m_fAngularVelocity = 0;

	//if (m_fAngularVelocity != 0)	cout << m_fAngularAcceleration << " | " << friction << endl;


	
}

void Collidable::updateSprite()
{
	m_sprite.setPosition(m_fvPosition.getX(), m_fvPosition.getY());
	m_sprite.setRotation(m_fOrientation * TO_DEGREES);
}

/*!
 *	Use both collidable's radii to check if they are close enough to justify checking for collision.
 *
 * \param pOtherCollidable Pointer to oher Collidable object.
 *
 * \return Whether they are close to each other or not.
 */
bool Collidable::broadCollisionCheck(shared_ptr<Collidable> pOtherCollidable)
{
	// Calculates distance of centers and sum of radii. Use squared values to avoid using sqrt().
	double fCentreDistSquared = (m_fvPosition - pOtherCollidable->getPosition()).squaredMagnitude();
	double fRadiiSumSquared = (m_fRadius + pOtherCollidable->getRadius()) * (m_fRadius + pOtherCollidable->getRadius());

	// Checks if the edges of the outter circles are colliding.
	if (fCentreDistSquared - fRadiiSumSquared <= 0) return true;
	else return false;
}

/*!
 *	Resolves overlap of two colliding objects and calculate impulses.
 *
 * \param pOtherCollidable Pointer to another collidable object.
 * \param pfvCollisionNormal Pointer to the collision normal vector.
 * \param fOverlap Amount of overlap between the two objects.
 * \param pfvContactPoint Pointer to contact point vector.
 */
void Collidable::resolveCollision(shared_ptr<Collidable> pOtherCollidable, Vector2D<double> * pfvCollisionNormal, double fOverlap, Vector2D<double> * pfvContactPoint)
{
	// Undoes the overlapping by moving back the other collidable.
	pOtherCollidable->setPosition(pOtherCollidable->getPosition() + (*pfvCollisionNormal * fOverlap));

	// The collision restitution coefficient is the minimum coefficient between the collidables.
	double fRestitution = min(m_fRestitution, pOtherCollidable->getRestitution());

	
	// Calculates distance from centres to contact point.
	Vector2D<double> fvDistCollidable = *pfvContactPoint - m_fvPosition;
	Vector2D<double> fvDistOtherCollidable = *pfvContactPoint - pOtherCollidable->getPosition();

	// Calculates relative velocity.
	//Vector2D<double> relVelocity = m_fvVelocity - otherCollidable->getVelocity();
	Vector2D<double> relativeVelocity = (m_fvVelocity + fvDistCollidable.crossProduct(m_fAngularVelocity)) - (pOtherCollidable->getVelocity() + fvDistOtherCollidable.crossProduct(pOtherCollidable->m_fAngularVelocity));
	// Checks if collidables are moving towards each other. If not, there is no reason to continue.
	if (relativeVelocity.dotProduct(pfvCollisionNormal) > 0) return;
	
	Vector2D<double> ra = *pfvContactPoint - m_fvPosition;
	Vector2D<double> rb = *pfvContactPoint - pOtherCollidable->getPosition();

	// Calculates impulse scalar (j).
	//double fImpulseScalar = -(1 + fRestitution) * relativeVelocity.dotProduct(pfvCollisionNormal) / (m_fInverseMass + pOtherCollidable->getInverseMass() + (m_fInverseMomentOfInertia*pow(ra.crossProduct(pfvCollisionNormal), 2)) + (pOtherCollidable->getInverseInertia() * pow(rb.crossProduct(pfvCollisionNormal), 2)));
	double fImpulseScalar = -(1 + fRestitution) * relativeVelocity.dotProduct(pfvCollisionNormal) / (m_fInverseMass + pOtherCollidable->getInverseMass());
	
	// Calculates impulses.
	Vector2D<double> fvImpulse = *pfvCollisionNormal * fImpulseScalar;
	applyImpulse(&fvImpulse, &fvDistCollidable);
	fvImpulse.flip();
	pOtherCollidable->applyImpulse(&fvImpulse, &fvDistOtherCollidable);
}

/*!
 * \param fvImpulse Impulse vector.
 * \param pfvContactPoint Pointer to contact point vector.
 */
void Collidable::applyImpulse(Vector2D<double> * pfvImpulse, Vector2D<double> * pfvContactPoint)
{
	Vector2D<double> ra = *pfvContactPoint - m_fvPosition;
	
	m_fvVelocity += (*pfvImpulse * m_fInverseMass);
	//m_fAngularVelocity += ra.crossProduct(pfvImpulse) * m_fInverseMomentOfInertia;
	//cout << (*pfvContactPoint).crossProduct(pfvImpulse) * m_fInverseMomentOfInertia << endl;
}

bool Collidable::isMoving()
{
	return m_fvVelocity.squaredMagnitude() > 0;
}

bool Collidable::isRotating()
{
	return m_fAngularVelocity != 0;
}

/*!
 * Draws object sprite to target.
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
	// stops collidable if it is below a minimum velocity.
	m_fvVelocity = velocity;
	if (m_fvVelocity.squaredMagnitude() < STOPPING_VELOCITY) m_fvVelocity = Vector2D<double>(0, 0);
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
	// Sets inverse mass. Prevents dividing by zero.
	if (fMass <= 0) m_fInverseMass = 0;
	else m_fInverseMass = 1.0 / fMass;
}
double Collidable::getInverseMass()
{
	return m_fInverseMass;
}

double Collidable::getMass()
{
	// Prevents dividing by zero.
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
	// Minimum radius is 1.
	if (fRadius >= 0) m_fRadius = fRadius;
	else m_fRadius = 1;
}

double Collidable::getInverseInertia()
{
	return m_fInverseMomentOfInertia;
}
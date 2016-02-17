//! \file circle.cpp Implementation of Circle class.

#include "circle.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

Circle::Circle()
{
	
}

/*! Initialize the position, radius and restitution coefficient with paramenters received.
 * The restitution coefficient can be omitted and, in this case, it will be set to 1 (fully elastic collision).
 *
 * \param fPosX,fPosY Coordinates for the position vector.
 * \param fRadius Radius of the object.
 * \param fRestitudion Restitution coefficient of object. Optional and, if omitted, set to 1.
 *
 */
Circle::Circle(double fPosX, double fPosY, double fRadius, double fRestitution)
{
	// Assign paramenters to respective member variables.
	m_fvPosition.setX(fPosX); m_fvPosition.setY(fPosY);
	m_fRadius = fRadius;
	m_fRestitution = fRestitution;
	// Assign default values
	m_fOrientation = 0; // Initial orientation is irrelevant for circular objects.
	setMass(0); // Make the object immovable.
	m_fFrictionCoefficient = 0; // As an immovable object, there is no friction coefficient.
	m_fInverseMomentOfInertia = 0; // As an immovable object, there is no moment of inertia.
}

/*! Used to solve "Double Dispatch" issue.
 *
 * \param pCollidable Pointer to an instance of any subclass of Collidable.
 */
void Circle::checkCollision(Collidable * pCollidable)
{
	pCollidable->checkCollision(this);
}

/*!
 * \param pOtherCircle Pointer to a Circle object.
 */
void Circle::checkCollision(Circle * pOtherCircle)
{
	// For collisions between two circles, a true broad test means there is a collision.
	if (broadCollisionCheck(pOtherCircle))
	{
		// Calculate the collision vector.
		Vector2D<double> fvCollisionNormal = (m_fvPosition - pOtherCircle->getPosition());
		// Calculate the overlap of the objects.
		double fOverlap = fvCollisionNormal.magnitude() - (m_fRadius + pOtherCircle->getRadius());
		
		// Normilize the collision vector.
		fvCollisionNormal.normalize();

		// Calculate contact point.
		Vector2D<double> fvContactPoint = pOtherCircle->getPosition() + (fvCollisionNormal * pOtherCircle->getRadius());

		// Resolve the collision.
		resolveCollision(pOtherCircle, &fvCollisionNormal, fOverlap, &fvContactPoint);
	}

}

/*!
* \param pObb Pointer to an OBB object.
*/
void Circle::checkCollision(OBB * pObb)
{
	// Perform a less costly broad check. If objects are not close enough, exit the function.
	if (!broadCollisionCheck(pObb)) return;

	// Calculate the distance between the centre of the objects.
	Vector2D<double> fvCentreDistance = m_fvPosition - pObb->getPosition();
	// Rotates the vector by the inverse of OBB's orientation so we can treat the OBB as an AABB.
	fvCentreDistance.rotate(-pObb->getOrientation());
	
	// Calculate the clamp vector for the collision.
	Vector2D<double> fvClamp;
	if (fvCentreDistance.getX() < 0) fvClamp.setX(std::max(fvCentreDistance.getX(), -pObb->getHalfExtents().getX()));
	if (fvCentreDistance.getX() >= 0) fvClamp.setX(std::min(fvCentreDistance.getX(), pObb->getHalfExtents().getX()));
	if (fvCentreDistance.getY() < 0) fvClamp.setY(std::max(fvCentreDistance.getY(), -pObb->getHalfExtents().getY()));
	if (fvCentreDistance.getY() >= 0) fvClamp.setY(std::min(fvCentreDistance.getY(), pObb->getHalfExtents().getY()));

	// Calculate the distance vector between OBB's edge and circle centre.
	Vector2D<double> fvDiff = fvCentreDistance - fvClamp;
	
	// If distance is smaller than the circle's radius, there is a collision.
	// Squared values are used to avois using SQRT() function when not necessary.
	if (fvDiff.squaredMagnitude() < (getRadius()*getRadius()))
	{
		// Calculate the overlap of the objects.
		double fOverlap = fvDiff.magnitude() - getRadius();

		// Rotate clamp to go back from and AABB to OBB.
		fvClamp.rotate(pObb->getOrientation());
		// Calculate collision vector subtracting the circle position from the point of contact.
		Vector2D<double> fvCollisionNormal = (m_fvPosition - fvClamp) - pObb->getPosition();
		// Normalize the collision vector.
		fvCollisionNormal.normalize();

		Vector2D<double> fvContactPoint = m_fvPosition + fvClamp;
		// Resolve collision
		resolveCollision(pObb, &fvCollisionNormal, fOverlap, &fvContactPoint);
		
	}
}

/*!
 * Use circle's attributes to fit the texture into the shape.
 *
 * \param pTexture Pointer to an SFML texture object.
 */
void Circle::setTexture(sf::Texture * pTexture)
{
	m_sprite.setTexture(*pTexture); // Set circle's sprite texture.
	m_sprite.setOrigin(pTexture->getSize().x / 2, pTexture->getSize().y / 2); // Set sprite's center as its origin (instead of its corner)
	m_sprite.scale(m_fRadius * 2 / pTexture->getSize().x, m_fRadius * 2 / pTexture->getSize().y); // Scale texture to make sure it fits the circle.
	m_sprite.setPosition(getPosition().getX(), getPosition().getY()); // Make the circle's and sprite's positions the same.
}



// to remove
void Circle::updatePoints()
{
	/*int iCirclePointNumber = 31;
	m_vaPoints.resize(iCirclePointNumber);
	for (int i = 0; i < iCirclePointNumber; i++) {
		double angle = (2 * M_PI) / (iCirclePointNumber - 1) * i;
		double x = m_fvPosition.getX() + m_fRadius * cos(angle);
		double y = m_fvPosition.getY() + m_fRadius * sin(angle);
		m_vaPoints[i].position = sf::Vector2f(x, y);
	}
	//*/
}
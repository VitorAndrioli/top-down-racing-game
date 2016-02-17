//! \file obb.cpp Implementation of OBB class.

#include "obb.h"
#include "circle.h"
#include "SFML\Graphics.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <array>

using namespace std;

OBB::OBB()
{
}

/*! Initialize the position, half -extents, orientation and restitution coefficient with paramenters received.
 * The restitution coefficient can be omitted and, in this case, it will be set to 1 (fully elastic collision).
 *
 * \param fPosX,fPosY Coordinates for the position vector.
 * \param fHalfExtentX,fHalfExtentY X and Y values of object's half-extents vector.
 * \param fRadius Radius of the object.
 * \param fRestitudion Restitution coefficient of object. Optional and, if omitted, set to 1.
 *
 */
OBB::OBB(double fPosX, double fPosY, double fHalfExtentX, double fHalfExtentY, double fOrientation, double fRestitution)
{
	// Assign paramenters to respective member variables.
	m_fvHalfExtents.setX(fHalfExtentX); m_fvHalfExtents.setY(fHalfExtentY);
	m_fvPosition.setX(fPosX); m_fvPosition.setY(fPosY);
	m_fOrientation = fOrientation;
	m_fRestitution = fRestitution;
	// Assign default values
	setMass(0); // Make the object immovable.
	m_fFrictionCoefficient = 0; // As an immovable object, there is no friction coefficient.
	m_fInverseMomentOfInertia = 0; // As an immovable object, there is no moment of inertia.
	m_fRadius = m_fvHalfExtents.magnitude(); // Get minimum radius that encapsulates the whole OBB. Used for broad collision checks.
}

void OBB::updatePoints()
{
	/*
	m_vaPoints.resize(5);
	Vector2D<double> rotationMatrixLine1(cos(m_fOrientation), -sin(m_fOrientation));
	Vector2D<double> rotationMatrixLine2(sin(m_fOrientation), cos(m_fOrientation));

	Vector2D<double> tempVector(-m_fvHalfExtents.getX(), m_fvHalfExtents.getY());
	tempVector.rotate(m_fOrientation);
	m_vaPoints[0].position.x = m_vaPoints[4].position.x = (tempVector + getPosition()).getX();
	m_vaPoints[0].position.y = m_vaPoints[4].position.y = (tempVector + getPosition()).getY();

	tempVector = Vector2D<double>(m_fvHalfExtents.getX(), m_fvHalfExtents.getY());
	tempVector.rotate(m_fOrientation);
	m_vaPoints[1].position.x = (tempVector + getPosition()).getX();
	m_vaPoints[1].position.y = (tempVector + getPosition()).getY();

	tempVector = Vector2D<double>(m_fvHalfExtents.getX(), -m_fvHalfExtents.getY());
	tempVector.rotate(m_fOrientation);
	m_vaPoints[2].position.x = (tempVector + getPosition()).getX();
	m_vaPoints[2].position.y = (tempVector + getPosition()).getY();

	tempVector = Vector2D<double>(-m_fvHalfExtents.getX(), -m_fvHalfExtents.getY());
	tempVector.rotate(m_fOrientation);
	m_vaPoints[3].position.x = (tempVector + getPosition()).getX();
	m_vaPoints[3].position.y = (tempVector + getPosition()).getY();
	//*/
}

/*! Used to solve "Double Dispatch" issue.
*
* \param pCollidable Pointer to an instance of any subclass of Collidable.
*/
void OBB::checkCollision(Collidable * pCollidable)
{
	pCollidable->checkCollision(this);
}

/*!
* \param pCircle Pointer to a Circle object.
*/
void OBB::checkCollision(Circle * pCircle)
{
	// Perform a less costly broad check. If objects are not close enough, exit the function.
	if (!broadCollisionCheck(pCircle)) return;

	// Calculate the distance between the centre of the objects.
	Vector2D<double> fvCentreDistance = pCircle->getPosition() - m_fvPosition;
	// Rotates the vector by the inverse of OBB's orientation so we can treat the OBB as an AABB.
	fvCentreDistance.rotate(-m_fOrientation);

	// Calculate the clamp vector for the collision.
	Vector2D<double> fvClamp;
	if (fvCentreDistance.getX() < 0) fvClamp.setX(std::max(fvCentreDistance.getX(), -m_fvHalfExtents.getX()));
	if (fvCentreDistance.getX() >= 0) fvClamp.setX(std::min(fvCentreDistance.getX(), m_fvHalfExtents.getX()));
	if (fvCentreDistance.getY() < 0) fvClamp.setY(std::max(fvCentreDistance.getY(), -m_fvHalfExtents.getY()));
	if (fvCentreDistance.getY() >= 0) fvClamp.setY(std::min(fvCentreDistance.getY(), m_fvHalfExtents.getY()));
	

	// Calculate the distance vector between OBB's edge and circle centre.
	Vector2D<double> fvDiff = fvCentreDistance - fvClamp;
	
	// If distance is smaller than the circle's radius, there is a collision.
	// Squared values are used to avois using SQRT() function when not necessary.
	if (fvDiff.squaredMagnitude() < (pCircle->getRadius()*pCircle->getRadius()))
	{
		// Calculate the overlap of the objects.
		double fOverlap = fvDiff.magnitude() - pCircle->getRadius();
		
		// Rotate clamp to go back from and AABB to OBB.
		fvClamp.rotate(m_fOrientation);
		// Calculate collision vector subtracting the circle position from the point of contact.
		Vector2D<double> fvCollisionNormal = (m_fvPosition + fvClamp) - pCircle->getPosition();
		// Normalize the collision vector.
		fvCollisionNormal.normalize();

		Vector2D<double> fvContactPoint = m_fvPosition + fvClamp;
		// Resolve collision
		resolveCollision(pCircle, &fvCollisionNormal, fOverlap, &fvContactPoint);
		//resolveCollision(pCircle, &fvCollisionNormal, fOverlap);
		
	}
}

/*!
 * Use the Separating Axis Theorem (SAT) to identify if two OBBs are colliding.
 *
 * \param pOtherObb Pointer to an OBB object.
 */
void OBB::checkCollision(OBB * pOtherObb)
{
	// Perform a less costly broad check. If objects are not close enough, exit the function.
	if (!broadCollisionCheck(pOtherObb)) return;

	// Create arrays to store both OBB's points in the 2D space.
	array<Vector2D<double>, 4> faObbPoints;
	array<Vector2D<double>, 4> faOtherObbPoints;

	// Get each of the four points of OBB.
	faObbPoints[0] = Vector2D<double>(m_fvHalfExtents.getX(), m_fvHalfExtents.getY());
	faObbPoints[1] = Vector2D<double>(m_fvHalfExtents.getX(), -m_fvHalfExtents.getY());
	faObbPoints[2] = Vector2D<double>(-m_fvHalfExtents.getX(), m_fvHalfExtents.getY());
	faObbPoints[3] = Vector2D<double>(-m_fvHalfExtents.getX(), -m_fvHalfExtents.getY());
	// Rotate all the points according to OBB orientation
	for (array<Vector2D<double>, 4>::iterator it = faObbPoints.begin(); it != faObbPoints.end(); ++it)
	{
		(*it).rotate(m_fOrientation);
		(*it) += m_fvPosition;
	}

	// Get each of the four points of other OBB.
	faOtherObbPoints[0] = Vector2D<double>(pOtherObb->getHalfExtents().getX(), pOtherObb->getHalfExtents().getY());
	faOtherObbPoints[1] = Vector2D<double>(pOtherObb->getHalfExtents().getX(), -pOtherObb->getHalfExtents().getY());
	faOtherObbPoints[2] = Vector2D<double>(-pOtherObb->getHalfExtents().getX(), pOtherObb->getHalfExtents().getY());
	faOtherObbPoints[3] = Vector2D<double>(-pOtherObb->getHalfExtents().getX(), -pOtherObb->getHalfExtents().getY());
	// Rotate all the points according to other OBB orientation
	for (array<Vector2D<double>, 4>::iterator it = faOtherObbPoints.begin(); it != faOtherObbPoints.end(); ++it)
	{
		(*it).rotate(pOtherObb->getOrientation());
		(*it) += pOtherObb->getPosition();
	}

	// Get both axes of the to OBBs to use on SAT.
	array<Vector2D<double>, 4> axis = {
		Vector2D<double>(cos(m_fOrientation), sin(m_fOrientation)),
		Vector2D<double>(-sin(m_fOrientation), cos(m_fOrientation)),
		Vector2D<double>(cos(pOtherObb->getOrientation()), sin(pOtherObb->getOrientation())),
		Vector2D<double>(-sin(pOtherObb->getOrientation()), cos(pOtherObb->getOrientation()))
	};

	Vector2D<double> fvCollisionNormal; // Collision Normal Vector
	double fMinimumOverlap = 99999; // Assign a high value to find the axis with the minimum overlap.
	

	for (array<Vector2D<double>, 4>::iterator it = axis.begin(); it != axis.end(); ++it)
	{
		double obb1min = 20000000;
		double obb1max = -20000000;

		double obb2min = 20000000;
		double obb2max = -20000000;

		for (int j = 0; j < 4; j++)
		{
			double dotProduct1 = (*it).dotProduct(&faObbPoints[j]);
			if (dotProduct1 < obb1min) obb1min = dotProduct1;
			if (dotProduct1 > obb1max) obb1max = dotProduct1;

			double dotProduct2 = (*it).dotProduct(&faOtherObbPoints[j]);
			if (dotProduct2 < obb2min) obb2min = dotProduct2;
			if (dotProduct2 > obb2max) obb2max = dotProduct2;
		}

		if (obb1max < obb2min || obb2max < obb1min) return;
		
		double overlap1 = obb1max - obb2min;
		double overlap2 = obb2max - obb1min;
		double overlap = min(overlap1, overlap2);

		if (overlap < finalOverlap)
		{
			fvCollisionNormal = (*it).unitVector();
			finalOverlap = overlap;
		}
				
	}
	
	Vector2D<double> relativePosition = m_fvPosition - pOtherObb->getPosition();
	if (relativePosition.dotProduct(&fvCollisionNormal) < 0) fvCollisionNormal.flip();

	//std::cout << collisionNormal.getX() << " | " << collisionNormal.getY() << " | " << (getPosition() - pOtherObb->getPosition()).dotProduct(&collisionNormal) << endl;
	resolveCollision(pOtherObb, &fvCollisionNormal, -finalOverlap);
	
}

void OBB::setTexture(sf::Texture * texture)
{
	m_sprite.setTexture(*texture);
	m_sprite.setOrigin(texture->getSize().x / 2, texture->getSize().y/2);
	//m_sprite.setTextureRect(sf::IntRect(0, 0, m_fvHalfExtents.getX() * 2, m_fvHalfExtents.getY() * 2));
	m_sprite.scale(m_fvHalfExtents.getX() * 2 / texture->getSize().x, m_fvHalfExtents.getY() * 2 / texture->getSize().y);
	//m_sprite.setColor(sf::Color(255, 255, 255, 128));

}


Vector2D<double> OBB::getHalfExtents()
{
	return m_fvHalfExtents;
}


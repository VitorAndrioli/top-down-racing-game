/*!
 * \file
 * \brief Implementation of OBB class.
 */

#include "obb.h"
#include <array>

OBB::OBB()
{
}

/*! 
 * Initializes position, half-extents, orientation and restitution coefficient with paramenters.
 * The restitution coefficient can be omitted and, in this case, it will be set to 1 (fully elastic collision).
 *
 * \param fPosX,fPosY Coordinates for the position vector.
 * \param fHalfExtentX,fHalfExtentY X and Y values of object's half-extents vector.
 * \param fRadius Radius of the object. Used for broad collision checks.
 * \param fRestitudion (Optional) Restitution coefficient of object. If omitted, it will be set to 1.
 */
OBB::OBB(double fPosX, double fPosY, double fHalfExtentX, double fHalfExtentY, double fOrientation, double fRestitution)
{
	// Assigns paramenters to respective member variables.
	setPosition(fPosX, fPosY);
	setHalfExtents(fHalfExtentX, fHalfExtentY);
	m_fOrientation = fOrientation;
	m_fRestitution = fRestitution;
	// Assigns default values
	setMass(0); // Makes the object immovable.
	m_fFrictionCoefficient = 0; // As an immovable object, there is no friction coefficient.
	m_fInverseMomentOfInertia = 0; // As an immovable object, there is no moment of inertia.
}

/*!
 * Method created to solve "Double Dispatch" issue.
 *
 * \param pCollidable Pointer to an instance of any subclass of Collidable.
 */
void OBB::checkCollision(Collidable* const pCollidable)
{
	pCollidable->checkCollision(this);
}

/*!
 * \param pCircle Pointer to a Circle object.
 */
void OBB::checkCollision(Circle* const pCircle)
{
	// Performs a less costly broad check. If objects are not close enough, exits the function.
	if (!broadCollisionCheck(pCircle)) return;

	// Calculates the distance between the centre of the objects.
	Vector2D<double> fvCentreDistance = pCircle->getPosition() - m_fvPosition;
	// Rotates the vector by the inverse of OBB's orientation so we can treat the OBB as an AABB.
	fvCentreDistance.rotate(-m_fOrientation);

	// Calculates the clamp vector for the collision.
	Vector2D<double> fvClamp;
	if (fvCentreDistance.getX() < 0) fvClamp.setX(max(fvCentreDistance.getX(), -m_fvHalfExtents.getX()));
	if (fvCentreDistance.getX() >= 0) fvClamp.setX(min(fvCentreDistance.getX(), m_fvHalfExtents.getX()));
	if (fvCentreDistance.getY() < 0) fvClamp.setY(max(fvCentreDistance.getY(), -m_fvHalfExtents.getY()));
	if (fvCentreDistance.getY() >= 0) fvClamp.setY(min(fvCentreDistance.getY(), m_fvHalfExtents.getY()));
	

	// Calculates the distance vector between OBB's edge and circle centre.
	Vector2D<double> fvDiff = fvCentreDistance - fvClamp;
	
	// If distance is smaller than the circle's radius, there is a collision.
	// Squared values are used to avois using SQRT() function when not necessary.
	if (fvDiff.squaredMagnitude() < (pCircle->getRadius()*pCircle->getRadius()))
	{
		// Calculates the overlap of the objects.
		double fOverlap = fvDiff.magnitude() - pCircle->getRadius();
		
		// Rotates clamp to go back from and AABB to OBB.
		fvClamp.rotate(m_fOrientation);
		// Calculates collision vector subtracting the circle position from the point of contact.
		Vector2D<double> fvCollisionNormal = (m_fvPosition + fvClamp) - pCircle->getPosition();
		// Normalizes the collision vector.
		fvCollisionNormal.normalize();

		Vector2D<double> fvContactPoint = m_fvPosition + fvClamp;
		// Resolves collision
		resolveCollision(pCircle, &fvCollisionNormal, fOverlap, &fvContactPoint);
	}
}

/*!
 * Uses the Separating Axis Theorem (SAT) to check for collision between two OBBs.
 *
 * \param pOtherObb Pointer to an OBB object.
 */
void OBB::checkCollision(OBB* const pOtherObb)
{
	// Performs a less costly broad check. If objects are not close enough, exit the function.
	if (!broadCollisionCheck(pOtherObb)) return;

	// Creates arrays to store both OBB's points in the 2D space.
	array<Vector2D<double>, 4> faObbPoints;
	array<Vector2D<double>, 4> faOtherObbPoints;

	// Gets each of the four points of OBB.
	faObbPoints[0] = Vector2D<double>(m_fvHalfExtents.getX(), m_fvHalfExtents.getY());
	faObbPoints[1] = Vector2D<double>(m_fvHalfExtents.getX(), -m_fvHalfExtents.getY());
	faObbPoints[2] = Vector2D<double>(-m_fvHalfExtents.getX(), m_fvHalfExtents.getY());
	faObbPoints[3] = Vector2D<double>(-m_fvHalfExtents.getX(), -m_fvHalfExtents.getY());
	// Rotates all the points according to OBB orientation
	for (array<Vector2D<double>, 4>::iterator it = faObbPoints.begin(); it != faObbPoints.end(); ++it)
	{
		(*it).rotate(m_fOrientation);
		(*it) += m_fvPosition;
	}

	// Gets each of the four points of other OBB.
	faOtherObbPoints[0] = Vector2D<double>(pOtherObb->getHalfExtents().getX(), pOtherObb->getHalfExtents().getY());
	faOtherObbPoints[1] = Vector2D<double>(pOtherObb->getHalfExtents().getX(), -pOtherObb->getHalfExtents().getY());
	faOtherObbPoints[2] = Vector2D<double>(-pOtherObb->getHalfExtents().getX(), pOtherObb->getHalfExtents().getY());
	faOtherObbPoints[3] = Vector2D<double>(-pOtherObb->getHalfExtents().getX(), -pOtherObb->getHalfExtents().getY());
	// Rotates all the points according to other OBB orientation
	for (array<Vector2D<double>, 4>::iterator it = faOtherObbPoints.begin(); it != faOtherObbPoints.end(); ++it)
	{
		(*it).rotate(pOtherObb->getOrientation());
		(*it) += pOtherObb->getPosition();
	}

	// Gets both axes of the to OBBs to use on SAT.
	array<Vector2D<double>, 4> axis = {
		Vector2D<double>(cos(m_fOrientation), sin(m_fOrientation)),
		Vector2D<double>(-sin(m_fOrientation), cos(m_fOrientation)),
		Vector2D<double>(cos(pOtherObb->getOrientation()), sin(pOtherObb->getOrientation())),
		Vector2D<double>(-sin(pOtherObb->getOrientation()), cos(pOtherObb->getOrientation()))
	};

	Vector2D<double> fvCollisionNormal; // Collision Normal Vector
	double fMinimumOverlap = 99999; // Used to find the axis with the minimum overlap.
	
	// Iterates trough every axis.
	for (array<Vector2D<double>, 4>::iterator it = axis.begin(); it != axis.end(); ++it)
	{
		// Declares variable to store maximum and minimum points of each OBB in this axis.
		double fObbMin = 99999,	fObbMax = -99999;
		double fOtherObbMin = 99999, fOtherObbMax = -99999;

		// Iterates trough every point of both OBBs to find the maximum and minimum values for this axis.
		for (int j = 0; j < 4; j++)
		{
			// Projects the point onto axis.
			double fObbPointProjection = (*it).dotProduct(&faObbPoints[j]);
			// Checks if it is minimum or maximum.
			if (fObbPointProjection < fObbMin) fObbMin = fObbPointProjection;
			if (fObbPointProjection > fObbMax) fObbMax = fObbPointProjection;

			// Projects the point onto axis.
			double fOtherObbPointProjection = (*it).dotProduct(&faOtherObbPoints[j]);
			// Checks if it is minimum or maximum.
			if (fOtherObbPointProjection < fOtherObbMin) fOtherObbMin = fOtherObbPointProjection;
			if (fOtherObbPointProjection > fOtherObbMax) fOtherObbMax = fOtherObbPointProjection;
		}

		// According to SAT, if there is no overlap in a single axis, there is no collision, thus we can exit the method.
		if (fObbMax < fOtherObbMin || fOtherObbMax < fObbMin) return;
		
		// Gets the overlap in this axis.
		double fOverlap = min((fObbMax - fOtherObbMin), (fOtherObbMax - fObbMin));

		// Checks if it is the minimum overlap.
		if (fOverlap < fMinimumOverlap)
		{
			fMinimumOverlap = fOverlap;
			// On SAT, the collision vector is the axis with the minimum overlap.
			fvCollisionNormal = (*it).unitVector();
		}
				
	}
	
	// Calculates the relative position of OBBs to know which direction the collision
	// normal should point to. Flip collision normal if necessary.
	Vector2D<double> fcRelativePosition = m_fvPosition - pOtherObb->getPosition();
	if (fcRelativePosition.dotProduct(&fvCollisionNormal) < 0) fvCollisionNormal.flip();


	Vector2D<double> fvContactPoint(0, 0);
	// Resolves collision
	resolveCollision(pOtherObb, &fvCollisionNormal, -fMinimumOverlap, &fvContactPoint);
	
}

// Setters and Getters.

/*!
 * The radius of and OBB is the minimum radius that embraces the whole box and, thus, depends on the half-extents
 *
 * \param fHalfExtentX,fHalfExtentY X and Y values of object's half-extents vector.
 */
void OBB::setHalfExtents(double fHalfExtentX, double fHalfExtentY)
{
	m_fvHalfExtents.setX(fHalfExtentX); m_fvHalfExtents.setY(fHalfExtentY);
	m_fRadius = m_fvHalfExtents.magnitude(); // Get minimum radius that encapsulates the whole OBB. Used for broad collision checks.
}

Vector2D<double> OBB::getHalfExtents()
{
	return m_fvHalfExtents;
}

/*!
 * Use OBB's attributes to fit the texture into the obb.
 *
 * \param pTexture Smart pointer to an SFML texture object.
 */
void OBB::setTexture(shared_ptr<sf::Texture> pTexture)
{
	if (!pTexture) return; // Checks if pointer is not null.
	m_sprite.setTexture(*pTexture); // Sets OBB's sprite texture.
	m_sprite.setOrigin(pTexture->getSize().x / 2, pTexture->getSize().y / 2); // Sets sprite's center as its origin (instead of its corner).
	m_sprite.scale(m_fvHalfExtents.getX() * 2 / pTexture->getSize().x, m_fvHalfExtents.getY() * 2 / pTexture->getSize().y); // Scales texture to make sure it fits the OBB.

	updateSprite();
}





void OBB::updatePoints()
{
	
	/*m_vaPoints.resize(5);
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


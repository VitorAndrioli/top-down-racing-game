#include "obb.h"
#include "circle.h"
#include "SFML\Graphics.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

OBB::OBB()
{

}

OBB::OBB(double dPosX, double dPosY, double dHalfExtentX, double dHalfExtentY, double dAngle)
{

	m_fvHalfExtents.setX(dHalfExtentX);
	m_fvHalfExtents.setY(dHalfExtentY);
	
	m_fvPosition.setX(dPosX);
	m_fvPosition.setY(dPosY);
		
	m_fAngle = dAngle * M_PI / 180; // angle is stored in radians
	m_fInverseMass = 1.0 / 50.0;
	
	m_vaPoints.resize(5);
}

Vector2D<double> OBB::getHalfExtents()
{
	return m_fvHalfExtents;
}

void OBB::updatePoints()
{
	
	Vector2D<double> rotationMatrixLine1(cos(m_fAngle), -sin(m_fAngle));
	Vector2D<double> rotationMatrixLine2(sin(m_fAngle), cos(m_fAngle));

	Vector2D<double> tempVector(
		-getHalfExtents().getX() * rotationMatrixLine1.getX() + getHalfExtents().getY() * rotationMatrixLine1.getY(),
		-getHalfExtents().getX() * rotationMatrixLine2.getX() + getHalfExtents().getY() * rotationMatrixLine2.getY());
	m_vaPoints[0].position.x = m_vaPoints[4].position.x = tempVector.add(&getPosition()).getX();
	m_vaPoints[0].position.y = m_vaPoints[4].position.y = tempVector.add(&getPosition()).getY();

	tempVector = Vector2D<double>(
		getHalfExtents().getX() * rotationMatrixLine1.getX() + getHalfExtents().getY() * rotationMatrixLine1.getY(),
		getHalfExtents().getX() * rotationMatrixLine2.getX() + getHalfExtents().getY() * rotationMatrixLine2.getY());
	m_vaPoints[1].position.x = tempVector.add(&getPosition()).getX();
	m_vaPoints[1].position.y = tempVector.add(&getPosition()).getY();

	tempVector = Vector2D<double>(
		getHalfExtents().getX() * rotationMatrixLine1.getX() - getHalfExtents().getY() * rotationMatrixLine1.getY(),
		getHalfExtents().getX() * rotationMatrixLine2.getX() - getHalfExtents().getY() * rotationMatrixLine2.getY());
	m_vaPoints[2].position.x = tempVector.add(&getPosition()).getX();
	m_vaPoints[2].position.y = tempVector.add(&getPosition()).getY();

	tempVector = Vector2D<double>(
		-getHalfExtents().getX() * rotationMatrixLine1.getX() - getHalfExtents().getY() * rotationMatrixLine1.getY(),
		-getHalfExtents().getX() * rotationMatrixLine2.getX() - getHalfExtents().getY() * rotationMatrixLine2.getY());
	m_vaPoints[3].position.x = tempVector.add(&getPosition()).getX();
	m_vaPoints[3].position.y = tempVector.add(&getPosition()).getY();
}

void OBB::checkCollision(Collidable * collidable)
{
	collidable->checkCollision(this);
}

void OBB::checkCollision(Circle * circle)
{
	Vector2D<double> newPosition = circle->getPosition().subtract(&getPosition());

	Vector2D <double> inverseRotationMatrixLine1(cos(-getAngle()), -sin(-getAngle()));
	Vector2D <double> inverseRotationMatrixLine2(sin(-getAngle()), cos(-getAngle()));

	Vector2D<double> newPosition2(newPosition.dotProduct(&inverseRotationMatrixLine1), newPosition.dotProduct(&inverseRotationMatrixLine2));

	Vector2D<double> dist = newPosition2;
	Vector2D<double> clamp;

	if (dist.getX() < 0) clamp.setX(std::max(dist.getX(), -getHalfExtents().getX()));
	if (dist.getX() >= 0) clamp.setX(std::min(dist.getX(), getHalfExtents().getX()));
	if (dist.getY() < 0) clamp.setY(std::max(dist.getY(), -getHalfExtents().getY()));
	if (dist.getY() >= 0) clamp.setY(std::min(dist.getY(), getHalfExtents().getY()));

	Vector2D<double> diff = dist.subtract(&clamp);
	double distance = diff.magnitude() - circle->getRadius();

	if (distance < 0)
	{
		Vector2D<double> collisionNormal = (circle->getPosition().subtract(&getPosition().add(&clamp))).unitVector();
		Vector2D<double> moveVector = getVelocity().unitVector().multiplyScalar(distance);

		setPosition(getPosition().add(&moveVector));

		resolveImpulse(circle, &collisionNormal);
	}
}

void OBB::checkCollision(OBB * obb)
{

}
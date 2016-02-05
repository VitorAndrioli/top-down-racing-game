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

OBB::OBB(double dPosX, double dPosY, double dHalfExtentX, double dHalfExtentY, double dAngle)
{
	m_fvHalfExtents.setX(dHalfExtentX);
	m_fvHalfExtents.setY(dHalfExtentY);
	
	m_fvPosition.setX(dPosX);
	m_fvPosition.setY(dPosY);
		
	setAngle(dAngle);
	setMass(50.0);
	
	m_vaPoints.resize(5);
}

void OBB::updatePoints()
{
	
	Vector2D<double> rotationMatrixLine1(cos(getAngle()), -sin(getAngle()));
	Vector2D<double> rotationMatrixLine2(sin(getAngle()), cos(getAngle()));

	Vector2D<double> tempVector(
		-getHalfExtents().getX() * rotationMatrixLine1.getX() + getHalfExtents().getY() * rotationMatrixLine1.getY(),
		-getHalfExtents().getX() * rotationMatrixLine2.getX() + getHalfExtents().getY() * rotationMatrixLine2.getY());
	m_vaPoints[0].position.x = m_vaPoints[4].position.x = (tempVector + getPosition()).getX();
	m_vaPoints[0].position.y = m_vaPoints[4].position.y = (tempVector + getPosition()).getY();

	tempVector = Vector2D<double>(
		getHalfExtents().getX() * rotationMatrixLine1.getX() + getHalfExtents().getY() * rotationMatrixLine1.getY(),
		getHalfExtents().getX() * rotationMatrixLine2.getX() + getHalfExtents().getY() * rotationMatrixLine2.getY());
	m_vaPoints[1].position.x = (tempVector + getPosition()).getX();
	m_vaPoints[1].position.y = (tempVector + getPosition()).getY();

	tempVector = Vector2D<double>(
		getHalfExtents().getX() * rotationMatrixLine1.getX() - getHalfExtents().getY() * rotationMatrixLine1.getY(),
		getHalfExtents().getX() * rotationMatrixLine2.getX() - getHalfExtents().getY() * rotationMatrixLine2.getY());
	m_vaPoints[2].position.x = (tempVector + getPosition()).getX();
	m_vaPoints[2].position.y = (tempVector + getPosition()).getY();

	tempVector = Vector2D<double>(
		-getHalfExtents().getX() * rotationMatrixLine1.getX() - getHalfExtents().getY() * rotationMatrixLine1.getY(),
		-getHalfExtents().getX() * rotationMatrixLine2.getX() - getHalfExtents().getY() * rotationMatrixLine2.getY());
	m_vaPoints[3].position.x = (tempVector + getPosition()).getX();
	m_vaPoints[3].position.y = (tempVector + getPosition()).getY();

}

void OBB::checkCollision(Collidable * collidable)
{
	collidable->checkCollision(this);
}

void OBB::checkCollision(Circle * circle)
{

	Vector2D<double> dist = circle->getPosition() - getPosition();
	dist.rotate(getAngle());

	Vector2D<double> clamp;

	if (dist.getX() < 0) clamp.setX(std::max(dist.getX(), -getHalfExtents().getX()));
	if (dist.getX() >= 0) clamp.setX(std::min(dist.getX(), getHalfExtents().getX()));
	if (dist.getY() < 0) clamp.setY(std::max(dist.getY(), -getHalfExtents().getY()));
	if (dist.getY() >= 0) clamp.setY(std::min(dist.getY(), getHalfExtents().getY()));

	Vector2D<double> diff = dist - clamp;
	double distance = diff.magnitude() - circle->getRadius();

	if (distance < 0)
	{
		Vector2D<double> collisionNormal = (circle->getPosition() - getPosition() + clamp).unitVector();
		Vector2D<double> moveVector = collisionNormal * (distance * 2);

		setPosition(getPosition() + moveVector);
		resolveImpulse(circle, &collisionNormal);
	}
}

void OBB::checkCollision(OBB * obb)
{
	array<Vector2D<double>, 4> obb1points;
	array<Vector2D<double>, 4> obb2points;

	Vector2D<double> rotationMatrixLine1(cos(getAngle()), -sin(getAngle()));
	Vector2D<double> rotationMatrixLine2(sin(getAngle()), cos(getAngle()));

	Vector2D<double> tempVector(
		-getHalfExtents().getX() * rotationMatrixLine1.getX() + getHalfExtents().getY() * rotationMatrixLine1.getY(),
		-getHalfExtents().getX() * rotationMatrixLine2.getX() + getHalfExtents().getY() * rotationMatrixLine2.getY());
	obb1points[0] = tempVector + getPosition();
	
	tempVector = Vector2D<double>(
		getHalfExtents().getX() * rotationMatrixLine1.getX() + getHalfExtents().getY() * rotationMatrixLine1.getY(),
		getHalfExtents().getX() * rotationMatrixLine2.getX() + getHalfExtents().getY() * rotationMatrixLine2.getY());
	obb1points[1] = tempVector + getPosition();
	
	tempVector = Vector2D<double>(
		getHalfExtents().getX() * rotationMatrixLine1.getX() - getHalfExtents().getY() * rotationMatrixLine1.getY(),
		getHalfExtents().getX() * rotationMatrixLine2.getX() - getHalfExtents().getY() * rotationMatrixLine2.getY());
	obb1points[2] = tempVector + getPosition();
	
	tempVector = Vector2D<double>(
		-getHalfExtents().getX() * rotationMatrixLine1.getX() - getHalfExtents().getY() * rotationMatrixLine1.getY(),
		-getHalfExtents().getX() * rotationMatrixLine2.getX() - getHalfExtents().getY() * rotationMatrixLine2.getY());
	obb1points[3] = tempVector + getPosition();
	
	rotationMatrixLine1 = Vector2D<double>(cos(obb->getAngle()), -sin(obb->getAngle()));
	rotationMatrixLine2 = Vector2D<double>(sin(obb->getAngle()), cos(obb->getAngle()));

	tempVector = Vector2D<double>(
		-obb->getHalfExtents().getX() * rotationMatrixLine1.getX() + obb->getHalfExtents().getY() * rotationMatrixLine1.getY(),
		-obb->getHalfExtents().getX() * rotationMatrixLine2.getX() + obb->getHalfExtents().getY() * rotationMatrixLine2.getY());
	obb2points[0] = tempVector + obb->getPosition();

	tempVector = Vector2D<double>(
		obb->getHalfExtents().getX() * rotationMatrixLine1.getX() + obb->getHalfExtents().getY() * rotationMatrixLine1.getY(),
		obb->getHalfExtents().getX() * rotationMatrixLine2.getX() + obb->getHalfExtents().getY() * rotationMatrixLine2.getY());
	obb2points[1] = tempVector + obb->getPosition();

	tempVector = Vector2D<double>(
		obb->getHalfExtents().getX() * rotationMatrixLine1.getX() - obb->getHalfExtents().getY() * rotationMatrixLine1.getY(),
		obb->getHalfExtents().getX() * rotationMatrixLine2.getX() - obb->getHalfExtents().getY() * rotationMatrixLine2.getY());
	obb2points[2] = tempVector + obb->getPosition();

	tempVector = Vector2D<double>(
		-obb->getHalfExtents().getX() * rotationMatrixLine1.getX() - obb->getHalfExtents().getY() * rotationMatrixLine1.getY(),
		-obb->getHalfExtents().getX() * rotationMatrixLine2.getX() - obb->getHalfExtents().getY() * rotationMatrixLine2.getY());
	obb2points[3] = tempVector + obb->getPosition();


	array<Vector2D<double>, 4> axis = {
		Vector2D<double>(cos(getAngle()), sin(getAngle())),
		Vector2D<double>(-sin(getAngle()), cos(getAngle())),
		Vector2D<double>(cos(obb->getAngle()), sin(obb->getAngle())),
		Vector2D<double>(-sin(obb->getAngle()), cos(obb->getAngle()))
	};

	Vector2D<double> collisionNormal;
	double finalOverlap = 999999;

	for (int i = 0; i < 4; i++)
	{
		double obb1min = 20000000;
		double obb1max = -20000000;

		double obb2min = 20000000;
		double obb2max = -20000000;

		for (int j = 0; j < 4; j++)
		{
			double dotProduct1 = axis[i].dotProduct(&obb1points[j]);
			if (dotProduct1 < obb1min) obb1min = dotProduct1;
			if (dotProduct1 > obb1max) obb1max = dotProduct1;

			double dotProduct2 = axis[i].dotProduct(&obb2points[j]);
			if (dotProduct2 < obb2min) obb2min = dotProduct2;
			if (dotProduct2 > obb2max) obb2max = dotProduct2;

		}

		if (obb1max < obb2min || obb2max < obb1min) return;
		
		double overlap1 = obb1max - obb2min;
		double overlap2 = obb2max - obb1min;
		double overlap = min(overlap1, overlap2);

		if (overlap <= finalOverlap)
		{
			collisionNormal = axis[i].unitVector();
			finalOverlap = overlap;
		}
		
	}
	
	if (collisionNormal.dotProduct(&obb->getVelocity()) > 0) finalOverlap *= -1;

	obb->setPosition(obb->getPosition() + collisionNormal * finalOverlap);

	resolveImpulse(obb, &collisionNormal);

}

Vector2D<double> OBB::getHalfExtents()
{
	return m_fvHalfExtents;
}


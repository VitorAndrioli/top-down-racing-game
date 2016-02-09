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
	setMass(dHalfExtentX*2);
	setRadius(m_fvHalfExtents.magnitude());

	m_fvInertia = (getMass() * (dHalfExtentX*dHalfExtentX + dHalfExtentY*dHalfExtentY))/12;

	m_vaPoints.resize(5);
}

void OBB::updatePoints()
{
	
	Vector2D<double> rotationMatrixLine1(cos(getAngle()), -sin(getAngle()));
	Vector2D<double> rotationMatrixLine2(sin(getAngle()), cos(getAngle()));

	Vector2D<double> tempVector(-getHalfExtents().getX(), getHalfExtents().getY());
	tempVector.rotate(getAngle());
	m_vaPoints[0].position.x = m_vaPoints[4].position.x = (tempVector + getPosition()).getX();
	m_vaPoints[0].position.y = m_vaPoints[4].position.y = (tempVector + getPosition()).getY();

	tempVector = Vector2D<double>(getHalfExtents().getX(), getHalfExtents().getY());
	tempVector.rotate(getAngle());
	m_vaPoints[1].position.x = (tempVector + getPosition()).getX();
	m_vaPoints[1].position.y = (tempVector + getPosition()).getY();

	tempVector = Vector2D<double>(getHalfExtents().getX(), -getHalfExtents().getY());
	tempVector.rotate(getAngle());
	m_vaPoints[2].position.x = (tempVector + getPosition()).getX();
	m_vaPoints[2].position.y = (tempVector + getPosition()).getY();

	tempVector = Vector2D<double>(-getHalfExtents().getX(), -getHalfExtents().getY());
	tempVector.rotate(getAngle());
	m_vaPoints[3].position.x = (tempVector + getPosition()).getX();
	m_vaPoints[3].position.y = (tempVector + getPosition()).getY();

}

void OBB::checkCollision(Collidable * collidable)
{
	collidable->checkCollision(this);
}

void OBB::checkCollision(Circle * circle)
{
	if (!broadCollisionCheck(circle)) return;

	Vector2D<double> fvCentreDistance = circle->getPosition() - getPosition();
	fvCentreDistance.rotate(-getAngle());

	Vector2D<double> fvClamp;
	if (fvCentreDistance.getX() < 0) fvClamp.setX(std::max(fvCentreDistance.getX(), -getHalfExtents().getX()));
	if (fvCentreDistance.getX() >= 0) fvClamp.setX(std::min(fvCentreDistance.getX(), getHalfExtents().getX()));
	if (fvCentreDistance.getY() < 0) fvClamp.setY(std::max(fvCentreDistance.getY(), -getHalfExtents().getY()));
	if (fvCentreDistance.getY() >= 0) fvClamp.setY(std::min(fvCentreDistance.getY(), getHalfExtents().getY()));
	

	Vector2D<double> fvDiff = fvCentreDistance - fvClamp;
	if (fvDiff.squaredMagnitude() < (circle->getRadius()*circle->getRadius()))
	{
		double fOverlap = fvDiff.magnitude() - circle->getRadius();
		
		fvClamp.rotate(getAngle());
		Vector2D<double> fvCollisionNormal = (fvClamp + getPosition() - circle->getPosition()).unitVector();
		
		resolveCollision(circle, &fvCollisionNormal, fOverlap);
	}
}

void OBB::checkCollision(OBB * obb)
{
	if (!broadCollisionCheck(obb)) return;

	array<Vector2D<double>, 4> obb1points;
	array<Vector2D<double>, 4> obb2points;

	obb1points[0] = Vector2D<double>(getHalfExtents().getX(), getHalfExtents().getY());
	obb1points[1] = Vector2D<double>(getHalfExtents().getX(), -getHalfExtents().getY());
	obb1points[2] = Vector2D<double>(-getHalfExtents().getX(), getHalfExtents().getY());
	obb1points[3] = Vector2D<double>(-getHalfExtents().getX(), -getHalfExtents().getY());
	for (auto it = obb1points.begin(); it != obb1points.end(); ++it)
	{
		(*it).rotate(getAngle());
		(*it) += getPosition();
	}

	obb2points[0] = Vector2D<double>(obb->getHalfExtents().getX(), obb->getHalfExtents().getY());
	obb2points[1] = Vector2D<double>(obb->getHalfExtents().getX(), -obb->getHalfExtents().getY());
	obb2points[2] = Vector2D<double>(-obb->getHalfExtents().getX(), obb->getHalfExtents().getY());
	obb2points[3] = Vector2D<double>(-obb->getHalfExtents().getX(), -obb->getHalfExtents().getY());
	for (auto it = obb2points.begin(); it != obb2points.end(); ++it)
	{
		(*it).rotate(obb->getAngle());
		(*it) += obb->getPosition();
	}

	array<Vector2D<double>, 4> axis = {
		Vector2D<double>(cos(getAngle()), sin(getAngle())),
		Vector2D<double>(-sin(getAngle()), cos(getAngle())),
		Vector2D<double>(cos(obb->getAngle()), sin(obb->getAngle())),
		Vector2D<double>(-sin(obb->getAngle()), cos(obb->getAngle()))
	};

	Vector2D<double> collisionNormal;
	double finalOverlap = 999999;
	double axisIndex = 0;

	for (auto it = axis.begin(); it != axis.end(); ++it)
	{
		double obb1min = 20000000;
		double obb1max = -20000000;

		double obb2min = 20000000;
		double obb2max = -20000000;

		for (int j = 0; j < 4; j++)
		{
			double dotProduct1 = (*it).dotProduct(&obb1points[j]);
			if (dotProduct1 < obb1min) obb1min = dotProduct1;
			if (dotProduct1 > obb1max) obb1max = dotProduct1;

			double dotProduct2 = (*it).dotProduct(&obb2points[j]);
			if (dotProduct2 < obb2min) obb2min = dotProduct2;
			if (dotProduct2 > obb2max) obb2max = dotProduct2;
		}

		if (obb1max < obb2min || obb2max < obb1min) return;
		
		double overlap1 = obb1max - obb2min;
		double overlap2 = obb2max - obb1min;
		double overlap = min(overlap1, overlap2);

		if (overlap <= finalOverlap)
		{
			collisionNormal = (*it).unitVector();
			finalOverlap = overlap;
			axisIndex = it - axis.begin();
		}
	}
	
	if (collisionNormal.dotProduct(&obb->getVelocity()) >= 0) finalOverlap *= -1;
	resolveCollision(obb, &collisionNormal, finalOverlap);
	
}

Vector2D<double> OBB::getHalfExtents()
{
	return m_fvHalfExtents;
}


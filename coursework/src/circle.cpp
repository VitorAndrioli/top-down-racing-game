#include "circle.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

Circle::Circle()
{

}

Circle::Circle(double fPosX, double fPosY, double fRadius, double fOrientation)
{
	m_fvPosition = Vector2D<double>(fPosX, fPosY);
	m_fRadius = fRadius;
	m_fOrientation = fOrientation;
	m_fInverseMass = 1/(fRadius*2);

	//m_fInverseMomentOfInertia = (getMass()*pow(getRadius(), 4)) / 4;
}

void Circle::checkCollision(Collidable * collidable)
{
	collidable->checkCollision(this);
}

void Circle::checkCollision(Circle * circle)
{
	if (broadCollisionCheck(circle))
	{
		Vector2D<double> fvCollisionNormal = (m_fvPosition - circle->getPosition());
		double fCentreDist = fvCollisionNormal.magnitude();
		double fRadiiSum = m_fRadius + circle->getRadius();
		double fOverlap = fCentreDist - fRadiiSum;
		
		fvCollisionNormal.normalize();
		resolveCollision(circle, &fvCollisionNormal, fOverlap);
	}

}

void Circle::checkCollision(OBB * obb)
{
	
	if (!broadCollisionCheck(obb)) return;

	Vector2D<double> fvCentreDistance = m_fvPosition - obb->getPosition();
	fvCentreDistance.rotate(-obb->getOrientation());
	
	Vector2D<double> fvClamp;
	if (fvCentreDistance.getX() < 0) fvClamp.setX(std::max(fvCentreDistance.getX(), -obb->getHalfExtents().getX()));
	if (fvCentreDistance.getX() >= 0) fvClamp.setX(std::min(fvCentreDistance.getX(), obb->getHalfExtents().getX()));
	if (fvCentreDistance.getY() < 0) fvClamp.setY(std::max(fvCentreDistance.getY(), -obb->getHalfExtents().getY()));
	if (fvCentreDistance.getY() >= 0) fvClamp.setY(std::min(fvCentreDistance.getY(), obb->getHalfExtents().getY()));

	Vector2D<double> fvDiff = fvCentreDistance - fvClamp;
	if (fvDiff.squaredMagnitude() < (getRadius()*getRadius()))
	{
		double fOverlap = fvDiff.magnitude() - getRadius();

		fvClamp.rotate(obb->getOrientation());
		Vector2D<double> fvCollisionNormal = m_fvPosition - fvClamp - obb->getPosition();
		fvCollisionNormal.normalize();
		resolveCollision(obb, &fvCollisionNormal, fOverlap);
	}
}

void Circle::updatePoints()
{
	int iCirclePointNumber = 31;
	m_vaPoints.resize(iCirclePointNumber);
	for (int i = 0; i < iCirclePointNumber; i++) {
		double angle = (2 * M_PI) / (iCirclePointNumber - 1) * i;
		double x = m_fvPosition.getX() + m_fRadius * cos(angle);
		double y = m_fvPosition.getY() + m_fRadius * sin(angle);
		m_vaPoints[i].position = sf::Vector2f(x, y);
	}
}
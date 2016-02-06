#include "circle.h"
#define _USE_MATH_DEFINES
#include <math.h>

Circle::Circle()
{

}

Circle::Circle(double fPosX, double fPosY, double fRadius, double fAngle)
{
	m_fvPosition.setX(fPosX);
	m_fvPosition.setY(fPosY);
	setRadius(fRadius);
	setAngle(fAngle);
	setMass(fRadius*2);

	m_fvInertia = (getMass()*pow(getRadius(), 4)) / 4;
}

void Circle::checkCollision(Collidable * collidable)
{
	collidable->checkCollision(this);
}

void Circle::checkCollision(Circle * circle)
{
	double fCentreDistSquared = (getPosition() - circle->getPosition()).squaredMagnitude();
	double fRadiiSumSquared = (getRadius() + circle->getRadius()) * (getRadius() + circle->getRadius());

	if (fCentreDistSquared - fRadiiSumSquared <= 0)
	{
		double fCentreDist = (getPosition() - circle->getPosition()).magnitude();
		double fRadiiSum = getRadius() + circle->getRadius();
		double fOverlap = fCentreDist - fRadiiSum;
		Vector2D<double> fvCollisionNormal = (getPosition() - circle->getPosition()).unitVector();
		
		resolveCollision(circle, &fvCollisionNormal, fOverlap);
	}
}

void Circle::checkCollision(OBB * obb)
{
	Vector2D<double> fvCentreDistance = getPosition() - obb->getPosition();
	fvCentreDistance.rotate(-obb->getAngle());
	
	Vector2D<double> fvClamp;
	if (fvCentreDistance.getX() < 0) fvClamp.setX(std::max(fvCentreDistance.getX(), -obb->getHalfExtents().getX()));
	if (fvCentreDistance.getX() >= 0) fvClamp.setX(std::min(fvCentreDistance.getX(), obb->getHalfExtents().getX()));
	if (fvCentreDistance.getY() < 0) fvClamp.setY(std::max(fvCentreDistance.getY(), -obb->getHalfExtents().getY()));
	if (fvCentreDistance.getY() >= 0) fvClamp.setY(std::min(fvCentreDistance.getY(), obb->getHalfExtents().getY()));

	Vector2D<double> fvDiff = fvCentreDistance - fvClamp;
	
	if (fvDiff.squaredMagnitude() < (getRadius()*getRadius()))
	{
		double fOverlap = fvDiff.magnitude() - getRadius();
		Vector2D<double> fvCollisionNormal = (getPosition() - obb->getPosition() + fvClamp).unitVector();
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

double Circle::getRadius()
{
	return m_fRadius;
}
void Circle::setRadius(double fRadius)
{
	if (fRadius >= 0)
		m_fRadius = fRadius;
	else
		m_fRadius = 1;
}
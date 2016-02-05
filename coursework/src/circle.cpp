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
}

void Circle::checkCollision(Collidable * collidable)
{
	collidable->checkCollision(this);
}

void Circle::checkCollision(Circle * circle)
{
	double centreDistSquared = (getPosition() - circle->getPosition()).squaredMagnitude();
	double radiiSumSquared = (getRadius() + circle->getRadius()) * (getRadius() + circle->getRadius());

	if (centreDistSquared - radiiSumSquared < 0)
	{
		double centreDist = (getPosition() - circle->getPosition()).magnitude();
		double radiiSum = getRadius() + circle->getRadius();

		Vector2D<double> collisionNormal = (getPosition() - circle->getPosition()).unitVector();
		setPosition(getPosition() - collisionNormal * (centreDist - radiiSum));

		resolveImpulse(circle, &collisionNormal);
	}
}

void Circle::checkCollision(OBB * obb)
{
	Vector2D<double> dist = getPosition() - obb->getPosition();
	dist.rotate(-obb->getAngle());
	
	Vector2D<double> clamp;
	if (dist.getX() < 0) clamp.setX(std::max(dist.getX(), -obb->getHalfExtents().getX()));
	if (dist.getX() >= 0) clamp.setX(std::min(dist.getX(), obb->getHalfExtents().getX()));
	if (dist.getY() < 0) clamp.setY(std::max(dist.getY(), -obb->getHalfExtents().getY()));
	if (dist.getY() >= 0) clamp.setY(std::min(dist.getY(), obb->getHalfExtents().getY()));

	Vector2D<double> diff = dist - clamp;
	double distance = diff.magnitude() - getRadius();

	if (distance < 0)
	{
		Vector2D<double> collisionNormal = (getPosition() - obb->getPosition() + clamp).unitVector();
		
		obb->setPosition(obb->getPosition() + collisionNormal * (distance * 2));
		resolveImpulse(obb, &collisionNormal);
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
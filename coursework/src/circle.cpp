#include "circle.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

Circle::Circle()
{

}

Circle::Circle(double dPosX, double dPosY, double dRadius)
{
	m_dvPosition = { dPosX, dPosY };
	m_dRadius = dRadius;

	update();
}

void Circle::draw()
{

}

double Circle::getRadius()
{
	return m_dRadius;
}

void Circle::moveRight()
{
	m_dvPosition.setX(m_dvPosition.getX() + 10);
	update();
}

void Circle::moveLeft()
{
	m_dvPosition.setX(m_dvPosition.getX() - 10);
	update();
}

void Circle::moveUp()
{
	m_dvPosition.setY(m_dvPosition.getY() - 10);
	update();
}

void Circle::moveDown()
{
	m_dvPosition.setY(m_dvPosition.getY() + 10);
	update();
}

void Circle::update()
{
	int iCirclePointNumber = 31;
	m_vaPoints.setPrimitiveType(sf::LinesStrip);
	m_vaPoints.resize(iCirclePointNumber);
	for (int i = 0; i < iCirclePointNumber; i++) {
		double angle = (2 * M_PI) / (iCirclePointNumber - 1) * i; // Degrees or Radians?
		double x = m_dvPosition.getX() + m_dRadius * cos(angle);
		double y = m_dvPosition.getY() + m_dRadius * sin(angle);
		m_vaPoints[i].position = sf::Vector2f(x, y);

	}
}
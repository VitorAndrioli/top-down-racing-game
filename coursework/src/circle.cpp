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

double Circle::getRadius()
{
	return m_dRadius;
}

void Circle::move(Vector<double> newPosition)
{
	m_dvPosition = m_dvPosition.sum(&newPosition);
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
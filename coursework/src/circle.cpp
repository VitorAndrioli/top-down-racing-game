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
}

void Circle::update(sf::Time elapsed)
{
	double maxVelocity = 130;
	double minVelocity = 0;

	//m_dVelocity = m_dVelocity + m_dAcceleration*elapsed.asSeconds();

	//if (m_dVelocity > maxVelocity) m_dVelocity = maxVelocity;
	//if (m_dVelocity < minVelocity) m_dVelocity = minVelocity;

	//std::cout << m_dVelocity << std::endl;

	m_dvVelocity.setX(cos(m_dAngle)*m_dVelocity);
	m_dvVelocity.setY(sin(m_dAngle)*m_dVelocity);

	m_dvPosition.setX(m_dvPosition.getX() + m_dvVelocity.getX() * elapsed.asSeconds());
	m_dvPosition.setY(m_dvPosition.getY() + m_dvVelocity.getY() * elapsed.asSeconds());


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

double Circle::getRadius()
{
	return m_dRadius;
}


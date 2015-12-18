#include <SFML\Graphics.hpp>
#include "car.h"
#include "vector.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace sf;

Car::Car(double dPosX, double dPosY, double dHalfExtentX, double dHalfExtentY, double dAngle)
{
	m_dvPosition = { dPosX, dPosY };
	m_dvHalfExtents = { dHalfExtentX, dHalfExtentY };
	m_dAngle = dAngle * M_PI / 180;
	m_dInverseMass = 1 / 50;
	m_dAcceleration = 0;
	m_dVelocity = 0;
	m_vaPoints.resize(5);
	m_vaPoints.setPrimitiveType(LinesStrip);

}

void Car::update(sf::Time elapsed)
{
	double maxVelocity = 130;
	double minVelocity = 0;

	m_dVelocity = m_dVelocity + m_dAcceleration*elapsed.asSeconds();
	
	if (m_dVelocity > maxVelocity) m_dVelocity = maxVelocity;
	if (m_dVelocity < minVelocity) m_dVelocity = minVelocity;

	std::cout << m_dVelocity << std::endl;

	m_dvVelocity.setX(cos(m_dAngle)*m_dVelocity);
	m_dvVelocity.setY(sin(m_dAngle)*m_dVelocity);

	m_dvPosition.setX(m_dvPosition.getX() + m_dvVelocity.getX() * elapsed.asSeconds());
	m_dvPosition.setY(m_dvPosition.getY() + m_dvVelocity.getY() * elapsed.asSeconds());

	Vector<double> rotationMatrixLine1(cos(m_dAngle), -sin(m_dAngle));
	Vector<double> rotationMatrixLine2(sin(m_dAngle), cos(m_dAngle));

	
	Vector<double> tempVector(
		-getHalfExtents().getX() * rotationMatrixLine1.getX() + getHalfExtents().getY() * rotationMatrixLine1.getY(),
		-getHalfExtents().getX() * rotationMatrixLine2.getX() + getHalfExtents().getY() * rotationMatrixLine2.getY() );
	m_vaPoints[0].position.x = m_vaPoints[4].position.x = tempVector.sum(&getPosition()).getX();
	m_vaPoints[0].position.y = m_vaPoints[4].position.y = tempVector.sum(&getPosition()).getY();
	
	tempVector = Vector<double>(
		getHalfExtents().getX() * rotationMatrixLine1.getX() + getHalfExtents().getY() * rotationMatrixLine1.getY(),
		getHalfExtents().getX() * rotationMatrixLine2.getX() + getHalfExtents().getY() * rotationMatrixLine2.getY());
	m_vaPoints[1].position.x = tempVector.sum(&getPosition()).getX();
	m_vaPoints[1].position.y = tempVector.sum(&getPosition()).getY();

	tempVector = Vector<double>(
		getHalfExtents().getX() * rotationMatrixLine1.getX() - getHalfExtents().getY() * rotationMatrixLine1.getY(),
		getHalfExtents().getX() * rotationMatrixLine2.getX() - getHalfExtents().getY() * rotationMatrixLine2.getY());
	m_vaPoints[2].position.x = tempVector.sum(&getPosition()).getX();
	m_vaPoints[2].position.y = tempVector.sum(&getPosition()).getY();

	tempVector = Vector<double>(
		-getHalfExtents().getX() * rotationMatrixLine1.getX() - getHalfExtents().getY() * rotationMatrixLine1.getY(),
		-getHalfExtents().getX() * rotationMatrixLine2.getX() - getHalfExtents().getY() * rotationMatrixLine2.getY());
	m_vaPoints[3].position.x = tempVector.sum(&getPosition()).getX();
	m_vaPoints[3].position.y = tempVector.sum(&getPosition()).getY();
}

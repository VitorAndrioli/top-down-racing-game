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

	m_vaPoints.resize(5);
	m_vaPoints.setPrimitiveType(LinesStrip);

	update();
}

void Car::rotate()
{
	setAngle(m_dAngle += (10 * M_PI / 180));
}

void Car::setAngle(double angle) {
	m_dAngle = angle;
	update();
}

void Car::moveRight()
{
	m_dvPosition.setX(m_dvPosition.getX() + 10);
	update();
}

void Car::moveLeft()
{
	m_dvPosition.setX(m_dvPosition.getX() - 10);
	update();
}

void Car::moveUp()
{
	m_dvPosition.setY(m_dvPosition.getY() - 10);
	update();
}

void Car::moveDown()
{
	m_dvPosition.setY(m_dvPosition.getY() + 10);
	update();
}

void Car::update()
{

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

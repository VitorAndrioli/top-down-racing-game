#include <SFML\Graphics.hpp>
#include "car.h"
#include "vector2D.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace sf;

Car::Car()
{

}

Car::Car(double dPosX, double dPosY, double dHalfExtentX, double dHalfExtentY, double dAngle)
{
	m_dvPosition = Vector2D<double>(dPosX, dPosY); 
	
	m_dvHalfExtents.setX(dHalfExtentX);
	m_dvHalfExtents.setY(dHalfExtentY);

	m_dAngle = dAngle * M_PI / 180;
	m_dInverseMass = 1 / 50;
	m_dAcceleration = 0;
	m_dVelocity = 0;
	m_dThrust = 0;
	m_vaPoints.resize(5);
	m_vaPoints.setPrimitiveType(LinesStrip);

}

void Car::update(float elapsed)
{
	
	Collidable::update(elapsed);
	OBB::update(elapsed);

}

#include <SFML\Graphics.hpp>
#include "car.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#define TO_RADIANS  M_PI / 180

using namespace sf;

Car::Car()
{

}

Car::Car(double dPosX, double dPosY, double dAngle) : OBB(dPosX, dPosY, 30, 19, dAngle)
{
	m_bReverse = false;
	m_bReversing = false;
	m_bAccelerating = false;
	m_bTurningLeft = false;
	m_bTurningRight = false;
	m_bMovingBackwards = false;
	m_bMovingForward = false;
	m_fMaxVelocity = 130;
	m_fWheelBase = 45;
	setSteeringAngle(dAngle);
	newCarAngle = m_fSteeringAngle;
	frontWheel = new OBB(dPosX + 20, dPosY, 6, 3.5, 0);
	setFrictionCoefficient(0.4);
	setMass(2050.0);
}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_vaPoints, states);
	target.draw(*frontWheel);
}

void Car::controlInput()
{
	m_fvThrust.setY(0);
	if (!m_bReversing && !m_bAccelerating)
	{
		m_fvThrust.setX(0);
	}
	else if (m_bAccelerating && m_bReversing)
	{
		m_fvThrust.setX(30);
	}
	else if (m_bAccelerating)
	{
		m_fvThrust.setX(130);
	}
	else
	{
		m_fvThrust.setX(-100);
	}

	m_fvThrust.rotate(getAngle());

	double wheelMaxLimit = 25*TO_RADIANS;
	double wheelMinLimit = 0.05*TO_RADIANS;
	double wheelTurnMovement = 0.02*TO_RADIANS;
	double wheelBackMovement = 0.08*TO_RADIANS;

	if (m_bTurningLeft && getSteeringAngle() > getAngle() - wheelMaxLimit)
		setSteeringAngle(getSteeringAngle() - wheelTurnMovement);

	if (m_bTurningRight && getSteeringAngle() < getAngle() + wheelMaxLimit)
		setSteeringAngle(getSteeringAngle() + wheelTurnMovement);

	if (!m_bTurningRight && !m_bTurningLeft)
		if (getSteeringAngle() > getAngle() + wheelMinLimit)
			setSteeringAngle(getSteeringAngle() - wheelBackMovement);
		else if (getSteeringAngle() < getAngle() - wheelMinLimit)
			setSteeringAngle(getSteeringAngle() + wheelBackMovement);
		else
			setSteeringAngle(getAngle());

}

void Car::update(float elapsed)
{
	controlInput();
	
	Vector2D<double> friction = m_fvVelocity * getFrictionCoefficient();
	m_fvAcceleration = m_fvThrust - friction;
	setVelocity(m_fvVelocity + m_fvAcceleration * elapsed);


	Vector2D<double> carOr(cos(m_fAngle), sin(m_fAngle));
	Vector2D<double> steeringOr(cos(m_fSteeringAngle), sin(m_fSteeringAngle));

	Vector2D<double> frontWheelPos = getPosition() + carOr * (m_fWheelBase / 2);
	Vector2D<double> rearWheelPos = getPosition() - carOr * (m_fWheelBase / 2);

	m_bReverse = carOr.dotProduct(&getVelocity()) < 0;

	double displacement = m_fvVelocity.magnitude() * elapsed;
	if (m_bReverse) displacement *= -1;
	
	Vector2D<double> frontWheel2 = frontWheelPos + (steeringOr * displacement);
	Vector2D<double> rearWheel2 = rearWheelPos + (carOr * displacement);
	setPosition((frontWheel2 + rearWheel2) / 2);
	
	newCarAngle = atan2((frontWheel2.getY() - rearWheel2.getY()), (frontWheel2.getX() - rearWheel2.getX()));
	double newSteeringAngle = m_fSteeringAngle + (newCarAngle-m_fAngle);
	
	setAngle(newCarAngle);
	m_fSteeringAngle = newSteeringAngle;
		
	frontWheel->update(elapsed);
	frontWheel->setPosition(frontWheelPos);
	frontWheel->setAngle(m_fSteeringAngle);
	
	updatePoints();
}

void Car::setVelocity(Vector2D<double> velocity)
{
	m_fvVelocity = velocity;

	if (abs(m_fvVelocity.squaredMagnitude()) > m_fMaxVelocity*m_fMaxVelocity && !m_bReverse)
	{
		m_fvVelocity.setX(m_fMaxVelocity*cos(getAngle()));
		m_fvVelocity.setY(m_fMaxVelocity*sin(getAngle()));
	}
	if (abs(m_fvVelocity.squaredMagnitude()) > 100*100 && m_bReverse)
	{
		m_fvVelocity.setX(-100*cos(getAngle()));
		m_fvVelocity.setY(-100 * sin(getAngle()));
	}

	if (abs(m_fvVelocity.squaredMagnitude()) < 0.1*0.1)
	{
		m_fvVelocity = Vector2D<double>(0, 0);
	}

	//std::cout << m_fvVelocity.magnitude() << std::endl;
}

void Car::setSteeringAngle(double fAngle)
{
	m_fSteeringAngle = fAngle;
}
double Car::getSteeringAngle()
{
	return m_fSteeringAngle;
}
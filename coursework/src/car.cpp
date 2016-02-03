#include <SFML\Graphics.hpp>
#include "car.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

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
	m_fSteeringAngle = dAngle * M_PI / 180;
	newCarAngle = m_fSteeringAngle;
	frontWheel = new OBB(dPosX + 20, dPosY, 6, 3.5, 0);
}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_vaPoints, states);
	target.draw(*frontWheel);
}

void Car::controlInput()
{
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

	m_fvThrust.rotate(m_fAngle);


	if (m_bTurningLeft)
		if (m_fSteeringAngle > m_fAngle - (25 * M_PI / 180))
			m_fSteeringAngle -= (0.02 * M_PI / 180);

	if (m_bTurningRight)
		if (m_fSteeringAngle < m_fAngle + (25 * M_PI / 180))
			m_fSteeringAngle += (0.02 * M_PI / 180);

	if (!m_bTurningRight && !m_bTurningLeft)
		if (m_fSteeringAngle > m_fAngle + 0.05)
			m_fSteeringAngle -= 0.08 * M_PI / 180;
		else if (m_fSteeringAngle < m_fAngle - 0.05)
			m_fSteeringAngle += 0.08 * M_PI / 180;
		else
			m_fSteeringAngle = m_fAngle;

}

void Car::update(float elapsed)
{
	controlInput();

	Vector2D<double> friction = m_fvVelocity.multiplyScalar(1);
	setAcceleration(m_fvThrust.subtract(&friction));
	setVelocity(m_fvVelocity.add(&m_fvAcceleration.multiplyScalar(elapsed)));

	Vector2D<double> carOr(cos(m_fAngle), sin(m_fAngle));
	Vector2D<double> steeringOr(cos(m_fSteeringAngle), sin(m_fSteeringAngle));

	Vector2D<double> frontWheelPos = getPosition().add(&carOr.multiplyScalar(m_fWheelBase / 2));
	Vector2D<double> rearWheelPos = getPosition().subtract(&carOr.multiplyScalar(m_fWheelBase / 2));

	double velocity = m_fvVelocity.magnitude();

	double fx = frontWheelPos.getX() + (steeringOr.getX() * velocity * elapsed);
	double fy = frontWheelPos.getY() + (steeringOr.getY() * velocity * elapsed);
	Vector2D<double> frontWheel2(fx, fy);
	
	double rx = rearWheelPos.getX() + (carOr.getX() * velocity * elapsed);
	double ry = rearWheelPos.getY() + (carOr.getY() * velocity * elapsed);
	Vector2D<double> rearWheel2(rx, ry);
	
	//std::cout << m_bAccelerating << "  " << m_bReversing << "  " << std::endl;

	/*Vector2D<double> frontWheel2 = frontWheelPos.add(&steeringOr.multiplyScalar(m_fvVelocity.magnitude()*elapsed*i));
	Vector2D<double> rearWheel2 = rearWheelPos.add(&carOr.multiplyScalar(m_fvVelocity.magnitude()*elapsed*i));
	*/
	setPosition(frontWheel2.add(&rearWheel2).divideScalar(2));

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

	if (abs(m_fvVelocity.squaredMagnitude()) > m_fMaxVelocity*m_fMaxVelocity && m_bAccelerating)
	{
		m_fvVelocity.setX(m_fMaxVelocity*cos(m_fAngle));
		m_fvVelocity.setY(m_fMaxVelocity*sin(m_fAngle));
	}

	if (abs(m_fvVelocity.squaredMagnitude()) < 0.1*0.1)
	{
		m_fvVelocity = Vector2D<double>(0, 0);
	}

	//std::cout << m_fvVelocity.magnitude() << std::endl;
}

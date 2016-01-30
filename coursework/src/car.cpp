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
	m_fSteeringAngle = dAngle * M_PI / 180;;
	frontWheel = new OBB(dPosX + 20, dPosY, 6, 3.5, 0);
	backWheel = new OBB(dPosX - 20, dPosY, 6, 3.5, 0);
}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(m_vaPoints, states);
	
	target.draw(*frontWheel);
}

void Car::update(float elapsed)
{

	if (!m_bReversing && !m_bAccelerating) m_dvThrust.setX(0);
	else if (m_bAccelerating && m_bReversing) m_dvThrust.setX(30);
	else if (m_bReversing) m_dvThrust.setX(-100);
	else m_dvThrust.setX(130);
	m_dvThrust.rotate(m_dAngle);


	Vector2D<double> friction = m_dvVelocity.multiplyScalar(1);
	m_dvAcceleration = m_dvThrust.subtract(&friction);
	m_dvVelocity = m_dvVelocity.add(&m_dvAcceleration.multiplyScalar(elapsed));

	double w = 40;

	Vector2D<double> carOr(cos(m_dAngle), sin(m_dAngle));
	Vector2D<double> steeringOr(cos(m_fSteeringAngle), sin(m_fSteeringAngle));

	Vector2D<double> frontWheelPos = getPosition().add(&carOr.multiplyScalar(w / 2));
	Vector2D<double> rearWheelPos = getPosition().subtract(&carOr.multiplyScalar(w / 2));

	double i = 1;
	if (m_bMovingBackwards) i = -1;
	
	Vector2D<double> frontWheel2 = frontWheelPos.add(&steeringOr.multiplyScalar(m_dvVelocity.magnitude()*elapsed*i));
	Vector2D<double> rearWheel2 = rearWheelPos.add(&carOr.multiplyScalar(m_dvVelocity.magnitude()*elapsed*i));
	
	m_dvPosition = frontWheel2.add(&rearWheel2).divideScalar(2);

	
	
	/*if (m_bTurningLeft)
		if (m_fSteeringAngle > m_dAngle - (25 * M_PI / 180))
			m_fSteeringAngle -= (0.02 * M_PI / 180);
	
	if (m_bTurningRight)
		if (m_fSteeringAngle < m_dAngle + (25 * M_PI / 180))
			m_fSteeringAngle += (0.02 * M_PI / 180);
	
	
	if (!m_bTurningRight && !m_bTurningLeft)
		if (m_fSteeringAngle > m_dAngle + 0.05)
			m_fSteeringAngle -= 0.08 * M_PI / 180;
		else if (m_fSteeringAngle < m_dAngle - 0.05)
			m_fSteeringAngle += 0.08 * M_PI / 180;
			else
				m_fSteeringAngle = m_dAngle;
	
	
	
	
	
	
	std::cout << friction.getX() << "  " << m_dvAcceleration.getX() << std::endl;
	
	///*
	
	std::cout << friction.getX() << "  " << m_dvAcceleration.getX() << std::endl;


	double newCarAngle = atan2( (fy-ry), (fx-rx) );
	double newSteeringAngle = m_fSteeringAngle + (newCarAngle-m_dAngle);
	
	m_dAngle = newCarAngle;
	m_fSteeringAngle = newSteeringAngle;
	//*/
	/*Vector2D<double> minVel(0.1, 0.1);

	Vector2D<double> maxVel(230, 0);
	maxVel.rotate(m_dAngle);

	if (abs(m_dvVelocity.squaredMagnitude()) > maxVel.squaredMagnitude() && m_bAccelerating)
	{
		m_dvVelocity = maxVel;
	}
	
	if (abs(m_dvVelocity.squaredMagnitude()) < minVel.squaredMagnitude())
	{
		m_dvVelocity = Vector2D<double>(0, 0);
	}

	///*
	frontWheel->update(elapsed);
	frontWheel->setPosition(frontWheelPos);
	frontWheel->setAngle(m_fSteeringAngle);
	*/

	updatePoints();
}

void Car::accelerate() {
	m_bAccelerating = true;
	m_bMovingForward = true;
	m_bMovingBackwards = false;
}

void Car::decelerate() {
	
}

void Car::reverse() {
	m_bReversing = true;
	m_bMovingForward = false;
	m_bMovingBackwards = true;
}

void Car::turnRight()
{
	m_bTurning = true;
	if (m_fSteeringAngle < m_dAngle + (25 * M_PI / 180))
		m_fSteeringAngle += (5 * M_PI / 180);
}

void Car::turnLeft()
{
	m_bTurning = true;
	if (m_fSteeringAngle > m_dAngle - (25 * M_PI / 180))
		m_fSteeringAngle -= (5 * M_PI / 180);
}

void Car::stopTurning()
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_bTurning = false;
	}
}


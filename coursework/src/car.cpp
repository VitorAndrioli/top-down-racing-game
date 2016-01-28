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
	m_fSteeringAngle = dAngle;
	frontWheel = new OBB(dPosX + 20, dPosY, 6, 3.5, 0);
	backWheel = new OBB(dPosX - 20, dPosY, 6, 3.5, 0);
}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(m_vaPoints, states);
	
	//target.draw(*frontWheel);
}

void Car::update(float elapsed)
{
	if (!m_bTurning)
	{
		//std::cout << m_fSteeringAngle << std::endl;
		if (m_fSteeringAngle > m_dAngle + 0.05)
			m_fSteeringAngle -= 1 * M_PI / 180;
		else if (m_fSteeringAngle < m_dAngle - 0.05)
			m_fSteeringAngle += 1 * M_PI / 180;
		else
			m_fSteeringAngle = m_dAngle;
		
	}

	Vector2D<double> friction = m_dvVelocity.multiplyScalar(m_fFrictionCoef);
	m_dvAcceleration = m_dvThrust.subtract(&friction);
	m_dvVelocity = m_dvVelocity.add(&m_dvAcceleration.multiplyScalar(elapsed));

	double w = 40;
	
	Vector2D<double> carOr(cos(m_dAngle), sin(m_dAngle));
	Vector2D<double> steeringOr(cos(m_fSteeringAngle), sin(m_fSteeringAngle));
	

	Vector2D<double> frontWheelPos = getPosition().add(&carOr.multiplyScalar(w / 2));
	Vector2D<double> rearWheelPos = getPosition().subtract(&carOr.multiplyScalar(w / 2));



	double fx = frontWheelPos.getX() + (steeringOr.getX()*m_dvVelocity.magnitude()*elapsed);
	double fy = frontWheelPos.getY() + (steeringOr.getY()*m_dvVelocity.magnitude()*elapsed);
	Vector2D<double> frontWheel2(fx, fy);
	
	double rx = rearWheelPos.getX() + (carOr.getX()*m_dvVelocity.magnitude()*elapsed);
	double ry = rearWheelPos.getY() + (carOr.getY()*m_dvVelocity.magnitude()*elapsed);
	Vector2D<double> rearWheel2(rx, ry);

	//std::cout << frontWheelPos.getY() << " -- " << (steeringOr.getY()*m_dvVelocity.magnitude()*elapsed) << std::endl;
	std::cout << m_dvVelocity.magnitude() << std::endl;
	
	m_dvPosition = frontWheel2.add(&rearWheel2).divideScalar(2);
	
	

	double newCarAngle = atan2( (fy-ry), (fx-rx) );
	double newSteeringAngle = m_fSteeringAngle + (newCarAngle-m_dAngle);
	
	m_dAngle = newCarAngle;
	m_fSteeringAngle = newSteeringAngle;

	//m_dvPosition = m_dvPosition.add(&m_dvVelocity.multiplyScalar(elapsed));


	//Collidable::update(elapsed);
	
	Vector2D<double> minVel(0.1, 0.1);

	Vector2D<double> maxVel(230, 0);
	maxVel.rotate(m_dAngle);

	if (abs(m_dvVelocity.squaredMagnitude()) > maxVel.squaredMagnitude())
	{
		m_dvVelocity = maxVel;
	}
	
	if (abs(m_dvVelocity.squaredMagnitude()) < minVel.squaredMagnitude())
	{
		m_dvVelocity = Vector2D<double>(0, 0);
	}

	//frontWheel->update(elapsed);
	//frontWheel->setPosition(frontWheelPos);
	//frontWheel->setAngle(m_fSteeringAngle);


	updatePoints();
}

void Car::accelerate() {
	m_dvThrust = Vector2D<double>(200, 0);
	m_dvThrust.rotate(m_dAngle);
}

void Car::decelerate() {
	m_dvThrust = Vector2D<double>(0, 0);
}

void Car::reverse() {
	m_dvThrust = Vector2D<double>(-30, 0);
	m_dvThrust.rotate(m_dAngle);
}

void Car::turnRight()
{
	//std::cout << "turnRight()" << std::endl;
	m_bTurning = true;
	if (m_fSteeringAngle < m_dAngle + (25 * M_PI / 180))
		m_fSteeringAngle += (5 * M_PI / 180);
}

void Car::turnLeft()
{
	//std::cout << "turnLeft()" << std::endl;
	m_bTurning = true;
	if (m_fSteeringAngle > m_dAngle - (25 * M_PI / 180))
		m_fSteeringAngle -= (5 * M_PI / 180);
}

void Car::stopTurning()
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		//std::cout << "stopTurning()" << std::endl;
		m_bTurning = false;
	}
}


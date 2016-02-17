//! \file car.cpp Implementation of Car class.

#include <SFML\Graphics.hpp>
#include "car.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>



using namespace sf;

Car::Car()
{

}

Car::Car(double fPosX, double fPosY, double fOrientation)
{
	m_bMovingForward = false;
	m_bReversing = false;
	m_bAccelerating = false;
	m_bTurningLeft = false;
	m_bTurningRight = false;
	m_bBraking = false;

	m_fvHalfExtents = Vector2D<double>(CAR_HALF_EXTENT_X, CAR_HALF_EXTENT_Y);
	m_fvPosition = Vector2D<double>(fPosX, fPosY);

	m_fOrientation = fOrientation;
	m_fSteeringOrientation = fOrientation;

	m_fRadius = m_fvHalfExtents.magnitude();
	
	m_vaPoints.resize(5);
	
	m_fMaxVelocity = MAXIMUM_SPEED;
	m_fWheelBase = CAR_WHEEL_BASE;
	
	m_rightFrontWheel = new OBB(fPosX + CAR_WHEEL_BASE, fPosY + CAR_FRONT_WHEEL_DISTANCE, 7, 3, 0);
	m_leftFrontWheel = new OBB(fPosX + CAR_WHEEL_BASE, fPosY - CAR_FRONT_WHEEL_DISTANCE, 7, 3, 0);
	
	m_fFrictionCoefficient = CAR_FRICTION_COEFFICIENT;
	m_fRestitution = CAR_RESTITUTION_COEFFICIENT;
	setMass(CAR_MASS);

	m_fInverseMomentOfInertia = 12 / (getMass() * (CAR_HALF_EXTENT_X*CAR_HALF_EXTENT_X + CAR_HALF_EXTENT_Y*CAR_HALF_EXTENT_Y));

}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_vaPoints, states);
	target.draw(*m_rightFrontWheel);
	target.draw(*m_leftFrontWheel);
	target.draw(m_sprite);
}

void Car::controlInput()
{
	m_fvThrust.setY(0);
	if (!m_bReversing && !m_bAccelerating) m_fvThrust.setX(0);
	else if (m_bAccelerating && m_bReversing) m_fvThrust.setX(500);
	else if (m_bAccelerating) m_fvThrust.setX(1000);
	else m_fvThrust.setX(-500);
	
	m_fvThrust.rotate(m_fOrientation);

	if (m_bBraking) m_sprite.setTextureRect(sf::IntRect(0, m_sprite.getTexture()->getSize().y / 2, m_sprite.getTexture()->getSize().x, m_sprite.getTexture()->getSize().y / 2));
	else m_sprite.setTextureRect(sf::IntRect(0,0, m_sprite.getTexture()->getSize().x, m_sprite.getTexture()->getSize().y / 2));

}

void Car::update(float elapsed)
{
	controlInput();
	steer();
	
	Vector2D<double> fvFriction = m_fvVelocity * getFrictionCoefficient();
	
	m_fvAcceleration = (m_fvThrust - fvFriction);// *m_fInverseMass;
	
	setVelocity( m_fvVelocity + m_fvAcceleration * elapsed );


	//std::cout << m_fvAcceleration.getX() << " | " << fvFriction.getY() << std::endl;


	
	
	Vector2D<double> fvCarOrientation(cos(m_fOrientation), sin(m_fOrientation));
	Vector2D<double> fvSteeringOr(cos(m_fSteeringOrientation), sin(m_fSteeringOrientation));

	Vector2D<double> frontWheelPos = getPosition() + fvCarOrientation * (m_fWheelBase / 2);
	Vector2D<double> rearWheelPos = getPosition() - fvCarOrientation * (m_fWheelBase / 2);

	double displacement = m_fvVelocity.magnitude() * elapsed;
	
	m_bMovingForward = fvCarOrientation.dotProduct(&getVelocity()) > 0;
	if (!m_bMovingForward) displacement *= -1;
	
	Vector2D<double> frontWheel2 = frontWheelPos + (fvSteeringOr * displacement);
	Vector2D<double> rearWheel2 = rearWheelPos + (fvCarOrientation * displacement);
	setPosition((frontWheel2 + rearWheel2) / 2);
	
	double newCarOrientation = atan2((frontWheel2.getY() - rearWheel2.getY()), (frontWheel2.getX() - rearWheel2.getX()));
	double newSteeringOrientation = m_fSteeringOrientation + (newCarOrientation-m_fOrientation);
	
	setOrientation(newCarOrientation);
	m_fSteeringOrientation = newSteeringOrientation;
		
	m_rightFrontWheel->updatePoints();
	m_leftFrontWheel->updatePoints();

	Vector2D<double> pos(0, CAR_FRONT_WHEEL_DISTANCE);
	pos.rotate(m_fOrientation);

	m_rightFrontWheel->setPosition(frontWheelPos + pos);
	m_leftFrontWheel->setPosition(frontWheelPos - pos);
	m_rightFrontWheel->setOrientation(m_fSteeringOrientation);
	m_leftFrontWheel->setOrientation(m_fSteeringOrientation);
	m_rightFrontWheel->updateSprite();
	m_leftFrontWheel->updateSprite();
	updateSprite();
	updatePoints();
}

void Car::setVelocity(Vector2D<double> velocity)
{
	m_fvVelocity = velocity;

	if (m_bMovingForward && abs(m_fvVelocity.squaredMagnitude()) > m_fMaxVelocity*m_fMaxVelocity)
	{
		m_fvVelocity.setX(m_fMaxVelocity*cos(getOrientation()));
		m_fvVelocity.setY(m_fMaxVelocity*sin(getOrientation()));
	}
	if (!m_bMovingForward && abs(m_fvVelocity.squaredMagnitude()) > MAXIMUM_REVERSE_SPEED_SQUARED)
	{
		m_fvVelocity.setX(-100*cos(getOrientation()));
		m_fvVelocity.setY(-100 * sin(getOrientation()));
	}


	if (abs(m_fvVelocity.squaredMagnitude()) < STOPPING_SPEED) m_fvVelocity = Vector2D<double>(0, 0);
	

	//std::cout << m_fvVelocity.magnitude() << std::endl;
}

void Car::steer()
{
	if (m_bTurningLeft && m_fSteeringOrientation > m_fOrientation - TYRE_MAXIMUM_ORIENTATION)
		m_fSteeringOrientation -= TYRE_MOVEMENT;

	if (m_bTurningRight && m_fSteeringOrientation < m_fOrientation + TYRE_MAXIMUM_ORIENTATION)
		m_fSteeringOrientation += TYRE_MOVEMENT;

	if (!m_bTurningRight && !m_bTurningLeft)
		if (m_fSteeringOrientation > m_fOrientation + TYRE_STOPPING_ORIENTATION)
			m_fSteeringOrientation -= TYRE_MOVEMENT;
		else if (m_fSteeringOrientation < m_fOrientation - TYRE_STOPPING_ORIENTATION)
			m_fSteeringOrientation += TYRE_MOVEMENT;
		else
			m_fSteeringOrientation = m_fOrientation;

}


void Car::setTexture(sf::Texture * texture)
{
	m_sprite.setTexture(*texture);
	texture->setSmooth(true);
	m_sprite.setOrigin(texture->getSize().x / 2, texture->getSize().y / 4);
	m_sprite.setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y/2));
	m_sprite.scale((m_fvHalfExtents.getX()+2) * 2 / texture->getSize().x, (m_fvHalfExtents.getY()+3) * 4 / texture->getSize().y);

}



void Car::setSteeringOrientation(double fOrientation)
{
	m_fSteeringOrientation = fOrientation;
}
double Car::getSteeringOrientation()
{
	return m_fSteeringOrientation;
}

double Car::getFrictionCoefficient()
{
	if (m_bBraking) return 15;
	else return m_fFrictionCoefficient;
}
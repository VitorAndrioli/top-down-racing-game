//! \file car.cpp Implementation of Car class.

#include <SFML\Graphics.hpp>
#include "car.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>



using namespace std;

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
	
	m_fWheelBase = WHEEL_BASE;
	
	m_fFrictionCoefficient = CAR_FRICTION_COEFFICIENT;
	m_fRestitution = CAR_RESTITUTION_COEFFICIENT;
	setMass(CAR_MASS);

	m_fInverseMomentOfInertia = 12 / (getMass() * (CAR_HALF_EXTENT_X*CAR_HALF_EXTENT_X + CAR_HALF_EXTENT_Y*CAR_HALF_EXTENT_Y));

}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_vaPoints, states);
	target.draw(m_frontRightWheel);
	target.draw(m_frontLeftWheel);
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
	
	//cout << m_bMovingForward << endl;
	
	Vector2D<double> fvFriction = m_fvVelocity * getFrictionCoefficient();
	m_fvAcceleration = (m_fvThrust - fvFriction);// *m_fInverseMass;
	setVelocity( m_fvVelocity + m_fvAcceleration * elapsed );

	Vector2D<double> fvCarOrientation(cos(m_fOrientation), sin(m_fOrientation));
	Vector2D<double> fvSteeringOr(cos(m_fSteeringOrientation), sin(m_fSteeringOrientation));

	Vector2D<double> frontWheelPos = m_fvPosition + fvCarOrientation * (m_fWheelBase / 2);
	Vector2D<double> rearWheelPos = m_fvPosition - fvCarOrientation * (m_fWheelBase / 2);

	double displacement = m_fvVelocity.magnitude() * elapsed;
	
	m_bMovingForward = fvCarOrientation.dotProduct(&m_fvVelocity) > 0; // TO FIX
	if (!m_bMovingForward) displacement *= -1;
	
	Vector2D<double> frontWheel2 = frontWheelPos + (fvSteeringOr * displacement);
	Vector2D<double> rearWheel2 = rearWheelPos + (fvCarOrientation * displacement);
	setPosition((frontWheel2 + rearWheel2) / 2);
		
	// TO DO 
	// Y displacement.

	double newCarOrientation = atan2((frontWheel2.getY() - rearWheel2.getY()), (frontWheel2.getX() - rearWheel2.getX()));
	double newSteeringOrientation = m_fSteeringOrientation + (newCarOrientation-m_fOrientation);
	
	setOrientation(newCarOrientation);
	m_fSteeringOrientation = newSteeringOrientation;
		
	Vector2D<double> pos(0, FRONT_WHEEL_DISTANCE);
	pos.rotate(m_fOrientation);

	updateSprite();
	updatePoints();
}

void Car::updateSprite()
{
	m_sprite.setPosition(m_fvPosition.getX(), m_fvPosition.getY());
	m_sprite.setRotation(m_fOrientation * TO_DEGREES);

	Vector2D<double> fvRightWheelPosition(WHEEL_BASE * 2, FRONT_WHEEL_DISTANCE);
	fvRightWheelPosition.rotate(m_fOrientation);
	m_frontRightWheel.setPosition((m_fvPosition + fvRightWheelPosition).getX(), (m_fvPosition + fvRightWheelPosition).getY());
	m_frontRightWheel.setRotation(m_fSteeringOrientation * TO_DEGREES);
	
	Vector2D<double> fvLeftWheelPosition(WHEEL_BASE * 2, -FRONT_WHEEL_DISTANCE);
	fvLeftWheelPosition.rotate(m_fOrientation);
	m_frontLeftWheel.setPosition((m_fvPosition + fvLeftWheelPosition).getX(), (m_fvPosition + fvLeftWheelPosition).getY());
	m_frontLeftWheel.setRotation(m_fSteeringOrientation * TO_DEGREES);

}

void Car::setVelocity(Vector2D<double> velocity)
{
	m_fvVelocity = velocity;

	if (m_bAccelerating && m_fvVelocity.squaredMagnitude() > MAXIMUM_SPEED*MAXIMUM_SPEED)
	{
		Vector2D<double> fvMaxSpeed(MAXIMUM_SPEED, 0);
		fvMaxSpeed.rotate(m_fOrientation);
		m_fvVelocity = fvMaxSpeed;
	}
	if (!m_bMovingForward && m_bReversing && m_fvVelocity.squaredMagnitude() > MAXIMUM_REVERSE_SPEED*MAXIMUM_REVERSE_SPEED)
	{
		Vector2D<double> fvMaxSpeed(-MAXIMUM_REVERSE_SPEED, 0);
		fvMaxSpeed.rotate(m_fOrientation);
		m_fvVelocity = fvMaxSpeed;
	}

	if (m_fvVelocity.squaredMagnitude() < STOPPING_SPEED) m_fvVelocity = Vector2D<double>(0, 0);
	

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

void Car::setWheelTexture(sf::Texture * texture)
{
	m_frontRightWheel.setTexture(*texture);
	texture->setSmooth(true);
	m_frontRightWheel.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
	m_frontRightWheel.setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
	m_frontRightWheel.scale(WHEEL_LENGHT / texture->getSize().x, WHEEL_WIDTH / texture->getSize().y);
	
	m_frontLeftWheel.setTexture(*texture);
	texture->setSmooth(true);
	m_frontLeftWheel.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
	m_frontLeftWheel.setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
	m_frontLeftWheel.scale(WHEEL_LENGHT / texture->getSize().x, WHEEL_WIDTH / texture->getSize().y);

}



double Car::getFrictionCoefficient()
{
	if (m_bBraking) return 15;
	else return m_fFrictionCoefficient;
}
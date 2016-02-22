/*!
 * \file
 * \brief Implementation of Car class.
 */

#include <SFML\Graphics.hpp>
#include "car.h"
#include <iostream>

Car::Car()
{

}

/*!
 * Initializes position and orientation with parameters
 * and  and assing default values to other member variables.
 *
 * \param fPosX,fPosY Coordinates for the position vector.
 * \param fOrientation (Optional) Orientation of the car. If omitted, it will be set to zero.
 */
Car::Car(double fPosX, double fPosY, double fOrientation) :
// Initialization list.
	m_bMovingForward(false),
	m_bReversing(false),
	m_bAccelerating(false),
	m_bTurningLeft(false),
	m_bTurningRight(false),
	m_bBraking(false),
	m_bBrakingSprite(false),
	m_display(MAXIMUM_SPEED)
{
	// Assigns paramenters to respective member variables.
	setPosition(fPosX, fPosY);
	m_fOrientation = fOrientation;
	m_fSteeringOrientation = fOrientation; // Orientation of the front wheels is, at start, the same as the car.
	
	// Assigns default values
	setHalfExtents(CAR_HALF_EXTENT_X, CAR_HALF_EXTENT_Y); // Uses setter method to set half-extents and radius.
	m_fWheelBase = WHEEL_BASE;
	m_fFrictionCoefficient = CAR_FRICTION_COEFFICIENT;
	m_fRestitution = CAR_RESTITUTION_COEFFICIENT;
	setMass(CAR_MASS);
	m_fInverseMomentOfInertia = 12 / (getMass() * (CAR_HALF_EXTENT_X*CAR_HALF_EXTENT_X + CAR_HALF_EXTENT_Y*CAR_HALF_EXTENT_Y)); // Equation for moment of inertia for rectangles.

	m_vaPoints.resize(5); // to remove
}

/*!
 * Implements mechanics for cars (motion and forces). 
 * Uses Improved Euler to integrate the velocity and
 * "Bicycle Steering" model for updating the position and orientation.
 *
 * \param fElapsed Time elapsed since last frame.
 */
void Car::update(float fElapsed)
{
	// Checks for player`s input.
	controlInput();

	// Calculates the friction of the object, based on the mass.
	Vector2D<double> fvFriction(getFrictionCoefficient() * getMass(), 0);
	fvFriction.rotate(m_fvVelocity.getOrientation());
	
	// Calculates air friction of the object, based on the velocity.
	Vector2D<double> fvAirFriction = (m_fvVelocity * 0.1);
	// Uses F = m.a equation to calculate the acceleration of the object.
	m_fvAcceleration = (m_fvThrust - fvAirFriction) * m_fInverseMass;
	// Friction only acts once the car is moving.
	if (isMoving()) m_fvAcceleration -= fvFriction;
	
	// Uses Improved Euler to calculate the velocity of the object.
	Vector2D<double> fvPredictedVelocity = m_fvVelocity + m_fvAcceleration * fElapsed;
	Vector2D<double> fvNewFriction = fvPredictedVelocity * getFrictionCoefficient();
	Vector2D<double> fvPredictedAcceleration = (m_fvThrust - fvNewFriction) * m_fInverseMass;

	setVelocity(m_fvVelocity + (m_fvAcceleration + fvPredictedAcceleration) * 0.5 * fElapsed);

	// Uses Bicycle Steering for updating car's position and orientation.
	// Gets vector for car's and steering's orientation.
	Vector2D<double> fvCarOrientation(cos(m_fOrientation), sin(m_fOrientation));
	Vector2D<double> fvSteeringOrientation(cos(m_fSteeringOrientation), sin(m_fSteeringOrientation));
	// Gets position from front and back wheels.
	Vector2D<double> fvFrontWheelPos = m_fvPosition + fvCarOrientation * (m_fWheelBase / 2);
	Vector2D<double> fvRearWheelPos = m_fvPosition - fvCarOrientation * (m_fWheelBase / 2);

	// Calculates displacement
	double displacement = m_fvVelocity.magnitude() * fElapsed;

	// Checking if car is current moving backwards. If so, changes direction of displacement.
	m_bMovingForward = fvCarOrientation.dotProduct(&m_fvVelocity) > 0; // TO FIX
	if (!m_bMovingForward) displacement *= -1;
	
	// Updates wheels position.
	fvFrontWheelPos += (fvSteeringOrientation * displacement);
	fvRearWheelPos += (fvCarOrientation * displacement);
	// Car's position is the average of wheels' positions.
	setPosition((fvFrontWheelPos + fvRearWheelPos) / 2);

	// Updates car's and wheels' orientation.
	double fOldCarOrientation = m_fOrientation;
	setOrientation( atan2((fvFrontWheelPos.getY() - fvRearWheelPos.getY()), (fvFrontWheelPos.getX() - fvRearWheelPos.getX())) );
	m_fSteeringOrientation += (m_fOrientation - fOldCarOrientation);

	// Updates car's sprites.
	updateSprite();

	// Updates analog display. Use squared velocity to avoid using sqrt() function.
	m_display.update(m_fvVelocity.squaredMagnitude());
	
	updatePoints(); // to remove.
}

/*!
 * Updates thrust for acceleration and reverse gear.
 * Change front wheels orientation (steering).
 */
void Car::controlInput()
{
	// Controls thrust.
	m_fvThrust.setY(0);
	if (!m_bReversing && !m_bAccelerating) m_fvThrust.setX(0);
	else if (m_bAccelerating) m_fvThrust.setX(500000);
	else m_fvThrust.setX(-400000);
	// Makes sure thrust is aligned with car.
	m_fvThrust.rotate(m_fOrientation);

	// Controls front wheel orientation.
	if (m_bTurningLeft && m_fSteeringOrientation > m_fOrientation - TYRE_MAXIMUM_ORIENTATION) m_fSteeringOrientation -= TYRE_MOVEMENT;
	if (m_bTurningRight && m_fSteeringOrientation < m_fOrientation + TYRE_MAXIMUM_ORIENTATION) m_fSteeringOrientation += TYRE_MOVEMENT;

	if (!m_bTurningRight && !m_bTurningLeft)
	{
		if (m_fSteeringOrientation > m_fOrientation + TYRE_STOPPING_ORIENTATION) m_fSteeringOrientation -= TYRE_MOVEMENT;
		else if (m_fSteeringOrientation < m_fOrientation - TYRE_STOPPING_ORIENTATION) m_fSteeringOrientation += TYRE_MOVEMENT;
		else m_fSteeringOrientation = m_fOrientation;
	}
}

void Car::updateSprite()
{
	// Changes texture rect to display braking texture when necessary.
	if (m_bBraking && !m_bBrakingSprite)
	{
		m_sprite.setTextureRect(sf::IntRect(0, m_sprite.getTexture()->getSize().y / 2, m_sprite.getTexture()->getSize().x, m_sprite.getTexture()->getSize().y / 2));
		m_bBrakingSprite = true;
	}
	else if (!m_bBraking && m_bBrakingSprite)
	{
		m_sprite.setTextureRect(sf::IntRect(0, 0, m_sprite.getTexture()->getSize().x, m_sprite.getTexture()->getSize().y / 2));
		m_bBrakingSprite = false;
	}
		
	// Updates texture position and orientation.
	m_sprite.setPosition(m_fvPosition.getX(), m_fvPosition.getY());
	m_sprite.setRotation(m_fOrientation * TO_DEGREES);

	// Updates wheels' position and orientation.
	Vector2D<double> fvRightWheelPosition(WHEEL_BASE * 2, FRONT_WHEEL_DISTANCE);
	fvRightWheelPosition.rotate(m_fOrientation); 
	fvRightWheelPosition += m_fvPosition;
	m_rightWheelSprite.setPosition(fvRightWheelPosition.getX(), fvRightWheelPosition.getY());
	m_rightWheelSprite.setRotation(m_fSteeringOrientation * TO_DEGREES);
	
	Vector2D<double> fvLeftWheelPosition(WHEEL_BASE * 2, -FRONT_WHEEL_DISTANCE);
	fvLeftWheelPosition.rotate(m_fOrientation);
	fvLeftWheelPosition += m_fvPosition;
	m_leftWheelSprite.setPosition(fvLeftWheelPosition.getX(), fvLeftWheelPosition.getY());
	m_leftWheelSprite.setRotation(m_fSteeringOrientation * TO_DEGREES);
}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Draw sprite of the car and of the front wheels.
	target.draw(m_rightWheelSprite);
	target.draw(m_leftWheelSprite);
	target.draw(m_sprite);
	target.draw(m_vaPoints, states); // remove
}

// Setters and getters

/*!
 * Use car's attributes to fit the texture into the car's OBB. 
 * The texture is divided in 2: A "normal" one and one with braking lights on, thus, the texture is managed as to draw only half of it.
 *
 * \param pTexture Smart pointer to an SFML texture object.
 */
void Car::setTexture(shared_ptr<sf::Texture> pTexture)
{
	if (!pTexture) return; // Checks if pointer is not null.
	m_sprite.setTexture(*pTexture); // Sets car's sprite texture.
	m_sprite.setOrigin(pTexture->getSize().x / 2, pTexture->getSize().y / 4); // Sets sprite's center as its origin (instead of its corner).
	m_sprite.setTextureRect(sf::IntRect(0, 0, pTexture->getSize().x, pTexture->getSize().y / 2)); // At first use non braking half of the texture.
	m_sprite.scale((m_fvHalfExtents.getX() + 1) * 2 / pTexture->getSize().x, (m_fvHalfExtents.getY() + 2) * 4 / pTexture->getSize().y); // Scales texture to make sure it fits the car.
	
	updateSprite();
}

/*!
 * Use car's default values to fit the wheels texture into wheels size. Both wheels use the same texture.
 *
 * \param pTexture Smart pointer to an SFML texture object.
 */
void Car::setWheelTexture(shared_ptr<sf::Texture> pTexture)
{
	if (!pTexture) return; // Checks if pointer is not null.
	// Sets right wheel texture.
	m_rightWheelSprite.setTexture(*pTexture); // Sets right wheel's sprite texture.
	m_rightWheelSprite.setOrigin(pTexture->getSize().x / 2, pTexture->getSize().y / 2); // Sets sprite's center as its origin (instead of its corner).
	m_rightWheelSprite.scale(WHEEL_LENGHT / pTexture->getSize().x, WHEEL_WIDTH / pTexture->getSize().y); // Scales texture to make sure it fits the car.
	// Sets right wheel texture.
	m_leftWheelSprite.setTexture(*pTexture);
	m_leftWheelSprite.setOrigin(pTexture->getSize().x / 2, pTexture->getSize().y / 2);
	m_leftWheelSprite.scale(WHEEL_LENGHT / pTexture->getSize().x, WHEEL_WIDTH / pTexture->getSize().y);

	updateSprite();
}

void Car::setVelocity(Vector2D<double> velocity)
{
	// Updates velocity.
	m_fvVelocity = velocity;

	// If moving forwards, makes sure it is not faster than maximum speed.
	if (m_bAccelerating && m_fvVelocity.squaredMagnitude() > MAXIMUM_SPEED*MAXIMUM_SPEED)
	{
		Vector2D<double> fvMaxSpeed(MAXIMUM_SPEED, 0);
		fvMaxSpeed.rotate(m_fOrientation);
		m_fvVelocity = fvMaxSpeed;
	}
	// If moving backwards, makes sure it is not faster than reverse maximum speed.
	if (!m_bMovingForward && m_bReversing && m_fvVelocity.squaredMagnitude() > MAXIMUM_REVERSE_SPEED*MAXIMUM_REVERSE_SPEED)
	{
		Vector2D<double> fvMaxSpeed(-MAXIMUM_REVERSE_SPEED, 0);
		fvMaxSpeed.rotate(m_fOrientation);
		m_fvVelocity = fvMaxSpeed;
	}

	// stops car if it is below a minimum velocity.
	if (m_fvVelocity.squaredMagnitude() < STOPPING_SPEED*STOPPING_SPEED && m_bBraking) m_fvVelocity = Vector2D<double>(0, 0);
	else if (m_fvVelocity.squaredMagnitude() < STOPPING_SPEED*STOPPING_SPEED && !m_bAccelerating && !m_bReversing) m_fvVelocity = Vector2D<double>(0, 0);
}

double Car::getFrictionCoefficient()
{
	if (m_bBraking) return CAR_REVERSE_FRICTION_COEFFICIENT;
	else return m_fFrictionCoefficient;
}

CarDisplay* Car::getDisplay()
{
	return &m_display;
}
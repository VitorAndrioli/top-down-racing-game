//! \file car.h Declaration of Car class.
/*!
* \class Car
*
* \brief Controlable car to be used by the player.
*
* Implements collision detection and texture allocation for circular objects.
* Can be used to turn background figures into immovable collidables. A circle instance is not drawn to the screen.
*
*/

#ifndef CAR_H
#define CAR_H

// Define constant values to be assigned for cars objects.
#define MAXIMUM_SPEED 230 //!< Maximum speed of the car.
#define STOPPING_SPEED 0.5 //!< Used to stop car with no shivering.
#define MAXIMUM_REVERSE_SPEED 100 * 100 //!< Default speed while going on reverse.
#define TYRE_MAXIMUM_ORIENTATION 25 * TO_RADIANS //!< Defines the limit the front wheels can turn.
#define TYRE_STOPPING_ORIENTATION 0.05 * TO_RADIANS //!< Define a minimum threshold to stop turning the wheels.
#define TYRE_MOVEMENT 0.5 * TO_RADIANS //!< Defines how much the wheels turn at each frame.
#define CAR_FRICTION_COEFFICIENT 0.1 //!< Default friction coefficient for car objects.
#define CAR_RESTITUTION_COEFFICIENT 0.6 //!< Default restitution coefficient for car objects.
#define CAR_MASS 100.0 //!< Default mass for car objects.
#define CAR_HALF_EXTENT_X 43 //!< Default X half-extent for car objects.
#define CAR_HALF_EXTENT_Y 20 //!< Default Y half-extent for car objects.
#define CAR_WHEEL_BASE (CAR_HALF_EXTENT_X*2) - 30  //!< Default distance between front and rear wheels for car objects.
#define CAR_FRONT_WHEEL_DISTANCE 19 //!< Default distance from centre to front wheels.

#include "obb.h"

class Car : public OBB
{
public:
	Car();
	Car(double fPosX, double fPosY, double fOrientation);
	void update(float elapsed);
	bool m_bMovingForward;

	sf::Texture tyreTexture;
	void setTexture(sf::Texture * texture);
	
	bool m_bTurningRight;
	bool m_bTurningLeft;
	bool m_bAccelerating;
	bool m_bReversing;
	bool m_bBraking;
		
	double m_fSteeringOrientation;
	double m_fWheelBase;
	OBB * m_rightFrontWheel;
	OBB * m_leftFrontWheel;
	void setVelocity(Vector2D<double> velocity);
	void setSteeringOrientation(double fOrientation);
	double getSteeringOrientation();
	double getFrictionCoefficient();
	void steer();
private:
	double m_fMaxVelocity;
	void controlInput();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
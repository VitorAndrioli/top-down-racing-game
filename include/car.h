/*!
 * \file
 * \brief Declaration of Car class.
 */

/*!
 * \class Car car.h "car.h"
 * \brief Controllable car to be used by the player.
 *
 * Implements mechanics for drivable objects, including acceleration, reverse gear, 
 * steering and braking, based on user inputs.
 * Also implements texture allocation for cars.
 *
 * \author Vitor Augusto Andrioli
 * \version 1.0
 * \date 25/02/2016
 *
 * \todo Add drift effect to car.
 *
 * \bug Turning while not accelerating (forwards or backwards) gets the car stuck. 
 * Method to identify whether the car is moving forward, to adjust bicycle steering, is defective.
 * \bug The car has no sideways displacement.
 */

#ifndef CAR_H
#define CAR_H

#include "obb.h"
#include "carDisplay.h"

// Definition of constant values to be assigned for cars objects.
#define MAXIMUM_SPEED 330 //!< Maximum speed of the car.
#define STOPPING_SPEED 8 //!< (Squared) Used to stop car with no shivering.
#define MAXIMUM_REVERSE_SPEED 230 //!< Default speed while going on reverse.
#define TYRE_MAXIMUM_ORIENTATION 25 * TO_RADIANS //!< Defines the limit the front wheels can rotate.
#define TYRE_STOPPING_ORIENTATION 0.05 * TO_RADIANS //!< Defines a minimum threshold to stop rotating the wheels.
#define TYRE_MOVEMENT 0.7 * TO_RADIANS //!< Defines how much the wheels rotate at each frame.
#define CAR_FRICTION_COEFFICIENT 0.1 //!< Default friction coefficient for car objects.
#define CAR_REVERSE_FRICTION_COEFFICIENT 1.1 //!< Default friction coefficient while on reverse gear for car objects.
#define CAR_RESTITUTION_COEFFICIENT 0.6 //!< Default restitution coefficient for car objects.
#define CAR_MASS 1500.f //!< Default mass for car objects.
#define CAR_HALF_EXTENT_X 37 //!< Default X half-extent for car objects.
#define CAR_HALF_EXTENT_Y 17 //!< Default Y half-extent for car objects.
#define WHEEL_BASE (CAR_HALF_EXTENT_X*2) - 25  //!< Default distance between front and rear wheels for car objects.
#define FRONT_WHEEL_DISTANCE 16 //!< Default (half) distance between front wheels.
#define WHEEL_LENGHT 12.f //!< Default wheel lenght.
#define WHEEL_WIDTH 5.f //!< Default wheel width.

using namespace std;

class Car : public OBB
{
public:
	Car(); //!< Basic constructor.
	Car(double fPosX, double fPosY, double fOrientation = 0); //!< Constructor initializing position and orientation.
	void update(float elapsed); //!< Override of Collidable's update method. To be called every frame of the game.

	// Control booleans.
	bool m_bMovingForward; //!< If car is current moving forward (NOT if the player is accelerating).
	bool m_bTurningRight; //!< If player is turning right.
	bool m_bTurningLeft; //!< If player is turning left.
	bool m_bAccelerating; //!< If player is acceleration.
	bool m_bReversing; //!< If player is activating reverse gear.
	bool m_bBraking; //!< If player is braking.

	// Setters and getters
	void setTexture(shared_ptr<sf::Texture> pTexture); //!< Override OBB's setTexture method.
	void setWheelTexture(shared_ptr<sf::Texture> pTexture); //!< Set front wheels texture.
	void setVelocity(Vector2D<double> fvVelocity); //!< Updates velocity. Checks for maximum and minimum normal and reverse speed.
	double getFrictionCoefficient(); //!< Returns different coefficient for reverse gear.
	CarDisplay* getDisplay(); //!< Get pointer to display (velocimeter).

protected:
	CarDisplay m_display; //<! Analog velocimeter.
	double m_fSteeringOrientation; //!< Orientation of front wheels.
	double m_fWheelBase; //!< Distance between front and rear wheels.
	sf::Sprite m_frontRightWheel; //!< Sprite for the right frontal wheel.
	sf::Sprite m_frontLeftWheel; //!< Sprite for the left frontal wheel.
	bool m_bBrakingSprite; //!< Which piece of texture is being used (braking or normal).
	void controlInput(); //!< Control the car according to control booleans.
	void updateSprite(); //!< Updates the sprites position and orientation. Changes sprite Rect while braking.

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const; //!< Virtual draw method inherited from Drawable class.
};

#endif
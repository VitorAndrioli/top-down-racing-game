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

// Definition of constant values to be assigned for cars objects.
#define MAXIMUM_SPEED 330 //!< Maximum speed of the car.
#define STOPPING_SPEED 8 //!< Used to stop car with no shivering.
#define MAXIMUM_REVERSE_SPEED 230 //!< Default speed while going on reverse.
#define TYRE_MAXIMUM_ORIENTATION 25 * TO_RADIANS //!< Defines the limit the front wheels can turn.
#define TYRE_STOPPING_ORIENTATION 0.05 * TO_RADIANS //!< Defines a minimum threshold to stop turning the wheels.
#define TYRE_MOVEMENT 0.7 * TO_RADIANS //!< Defines how much the wheels turn at each frame.
#define CAR_FRICTION_COEFFICIENT 0.1 //!< Default friction coefficient for car objects.
#define CAR_RESTITUTION_COEFFICIENT 0.6 //!< Default restitution coefficient for car objects.
#define CAR_MASS 1500.f //!< Default mass for car objects.
#define CAR_HALF_EXTENT_X 37 //!< Default X half-extent for car objects.
#define CAR_HALF_EXTENT_Y 17 //!< Default Y half-extent for car objects.
#define WHEEL_BASE (CAR_HALF_EXTENT_X*2) - 25  //!< Default distance between front and rear wheels for car objects.
#define FRONT_WHEEL_DISTANCE 16 //!< Default (half) distance between front wheels.
#define WHEEL_LENGHT 12.f //!< Default wheel lenght.
#define WHEEL_WIDTH 5.f //!< Default wheel width.

#include "obb.h"

using namespace std;

class Car : public OBB
{
public:
	Car(); //!< Basic constructor. Does not initialize any member variable.
	Car(double fPosX, double fPosY, double fOrientation = 0); //!< Constructor receiving position and orientation.
	void update(float elapsed); //!< Override Collidable's update method. To be called every frame of the game.
	
	// Control booleans.
	bool m_bMovingForward; //!< If car is current moving forward (NOT if the player is accelerating).
	bool m_bTurningRight; //!< If player is turning right.
	bool m_bTurningLeft; //!< If player is turning left.
	bool m_bAccelerating; //!< If player is acceleration.
	bool m_bReversing; //!< If player is activating reverse gear.
	bool m_bBraking; //!< If player is braking.
	
	double m_fSteeringOrientation; //!< Orientation of front wheels.
	double m_fWheelBase; //!< Distance between front and rear wheels.
	
	sf::Sprite m_frontRightWheel; //!< Sprite for the right front wheel.
	sf::Sprite m_frontLeftWheel; //!< Sprite for the right front wheel.

	// Setters and getters
	void setTexture(shared_ptr<sf::Texture> pTexture); //!< Override OBB's setTexture method.
	void setWheelTexture(shared_ptr<sf::Texture> pTexture); //!< Set front wheels texture.
	void setVelocity(Vector2D<double> fvVelocity); //!< Updates velocity. Checks for maximum and maximum reverse speed.
	double getFrictionCoefficient(); //!< Returns different coefficient for reverse gear.
private:
	bool m_bBrakingSprite; //!< Which piece of texture is being used (braking or normal).
	void controlInput(); //!< Control the car according to control booleans.
	void updateSprite(); //!< Updates the sprite position and orientation. Changes sprite Rect when braking.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //!< Virtual draw method inherited from Drawable class.
};

#endif
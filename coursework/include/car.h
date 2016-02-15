//! \file car.h Declaration of Car class.

#ifndef CAR_H
#define CAR_H

#define MAXIMUM_SPEED 230
#define STOPPING_SPEED 0.05
#define MAXIMUM_REVERSE_SPEED_SQUARED 100 * 100
#define TYRE_MAXIMUM_ORIENTATION 25 * TO_RADIANS
#define TYRE_STOPPING_ORIENTATION 0.05 * TO_RADIANS
#define TYRE_MOVEMENT 0.5 * TO_RADIANS

#define CAR_FRICTION_COEFFICIENT 0.72
#define CAR_RESTITUTION_COEFFICIENT 0.6
#define CAR_MASS 1000.0
#define CAR_HALF_EXTENT_X 43
#define CAR_HALF_EXTENT_Y 20
#define CAR_WHEEL_BASE 50
#define CAR_FRONT_WHEEL_DISTANCE 20

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
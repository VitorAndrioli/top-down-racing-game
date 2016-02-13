#ifndef CAR_H
#define CAR_H

#define MAXIMUM_SPEED 130
#define STOPPING_SPEED 0.1
#define MAXIMUM_REVERSE_SPEED_SQUARED 100 * 100
#define TYRE_MAXIMUM_ORIENTATION 25 * TO_RADIANS
#define TYRE_STOPPING_ORIENTATION 0.05 * TO_RADIANS
#define TYRE_MOVEMENT 0.5 * TO_RADIANS

#include "obb.h"

class Car : public OBB
{
public:
	Car();
	Car(double fPosX, double fPosY, double fOrientation);
	void update(float elapsed);
	bool m_bMovingForward;
	
	bool m_bTurningRight;
	bool m_bTurningLeft;
	bool m_bAccelerating;
	bool m_bReversing;
	bool m_bBraking;
		
	double m_fSteeringOrientation;
	double m_fWheelBase;
	OBB * frontWheel;
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
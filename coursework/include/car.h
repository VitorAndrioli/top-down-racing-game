#ifndef CAR_H
#define CAR_H

#include "obb.h"

class Car : public OBB
{
public:
	Car();
	Car(double dPosX, double dPosY, double dAngle);
	void update(float elapsed);
	double newCarAngle;
	bool m_bMovingForward;
	
	bool m_bTurningRight;
	bool m_bTurningLeft;
	bool m_bAccelerating;
	bool m_bReversing;
	bool m_bBraking;
		
	double m_fSteeringAngle;
	double m_fWheelBase;
	OBB * frontWheel;
	void setVelocity(Vector2D<double> velocity);
	void setSteeringAngle(double fAngle);
	double getSteeringAngle();
	double getFrictionCoefficient();
	void steer();
private:
	double m_fMaxVelocity;
	void controlInput();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
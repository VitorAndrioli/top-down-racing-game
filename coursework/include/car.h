#ifndef CAR_H
#define CAR_H

#include "obb.h"

class Car : public OBB
{
public:
	Car();
	Car(double dPosX, double dPosY, double dAngle);
	void setAngle(double angle);
	void update(float elapsed);
	void accelerate();
	void decelerate();
	void reverse();
	void turnRight();
	void turnLeft();
	void stopTurning();
	bool m_bReverse;
	bool m_bTurning;
	double m_fSteeringAngle;
	OBB * frontWheel;
	OBB * backWheel;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
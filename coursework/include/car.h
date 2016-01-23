#ifndef CAR_H
#define CAR_H

#include "obb.h";

class Car : public OBB
{
public:
	Car();
	Car(double dPosX, double dPosY, double dAngle);
	void update(float elapsed);
	void setAngle(double angle);
};

#endif
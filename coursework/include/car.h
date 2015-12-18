#ifndef CAR_H
#define CAR_H

#include "obb.h";

class Car : public OBB
{
public:
	Car(double dPosX, double dPosY, double dHalfExtentX, double dHalfExtentY, double dAngle);
	void update(sf::Time elapsed);
	void setAngle(double angle);
};

#endif
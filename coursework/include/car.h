#ifndef CAR_H
#define CAR_H

#include "obb.h"

class Car : public OBB
{
public:
	Car();
	Car(double dPosX, double dPosY, double dAngle);
	void setAngle(double angle);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
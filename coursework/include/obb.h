#ifndef OBB_H
#define OBB_H

#include "collidable.h"

class OBB : public Collidable
{
protected:
	Vector2D<double> m_dvHalfExtents;
public:
	OBB();
	OBB(double dPosX, double dPosY, double dHalfExtentX, double dHalfExtentY, double dAngle);
	void updatePoints();
	Vector2D<double> getHalfExtents();
};

#endif
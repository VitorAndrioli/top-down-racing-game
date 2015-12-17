#ifndef OBB_H
#define OBB_H

#include "collidable.h"

class OBB : public Collidable
{
protected:
	Vector<double> m_dvHalfExtents;
public:
	OBB();
	OBB(double dPosX, double dPosY, double dHalfExtentX, double dHalfExtentY, double dAngle);
	Vector<double> getHalfExtents();
private:
	void draw();
	void update();
};

#endif
#ifndef OBB_H
#define OBB_H

#include "collidable.h"

class OBB : public Collidable
{
protected:
	Vector2D<double> m_fvHalfExtents;
public:
	OBB();
	OBB(double fPosX, double fPosY, double fHalfExtentX, double fHalfExtentY, double fOrientation);
	void updatePoints();
	Vector2D<double> getHalfExtents();
	void setHalfExtents(Vector2D<double>);
	void checkCollision(Collidable * collidable);
	void checkCollision(Circle * circle);
	void checkCollision(OBB * obb);
};

#endif
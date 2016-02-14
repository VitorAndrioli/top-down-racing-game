#pragma once

#include "obb.h"

class Box : public OBB
{
public:
	Box();
	Box(double fPosX, double fPosY, double fSize);
	Box(double fPosX, double fPosY, double fSize, double fOrientation);
	~Box();
};


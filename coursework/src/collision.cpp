#include "collision.h"
#include "vector.h"
#include <iostream>
#include <array>

using namespace std;

Collision::Collision()
{
}


bool Collision::checkCollision(OBB * obb1, OBB * obb2)
{

	array<double, 4> rotationMatrix1 = { cos(obb1->getAngle()), sin(obb1->getAngle()), -sin(obb1->getAngle()), cos(obb1->getAngle()) };
	array<double, 4> rotationMatrix2 = { cos(obb2->getAngle()), sin(obb2->getAngle()), -sin(obb2->getAngle()), cos(obb2->getAngle()) };


	array<Vector<double>, 4> obb1points;
	array<Vector<double>, 4> obb2points;

	obb1points[0] = Vector<double>(
		obb1->getPosition().getX() - obb1->getHalfExtents().getX() * rotationMatrix1[0] + obb1->getHalfExtents().getY() * rotationMatrix1[1],
		obb1->getPosition().getY() - obb1->getHalfExtents().getX() * rotationMatrix1[2] + obb1->getHalfExtents().getY() * rotationMatrix1[3]
		);

	obb1points[1] = Vector<double>(
		obb1->getPosition().getX() + obb1->getHalfExtents().getX() * rotationMatrix1[0] + obb1->getHalfExtents().getY() * rotationMatrix1[1],
		obb1->getPosition().getY() + obb1->getHalfExtents().getX() * rotationMatrix1[2] + obb1->getHalfExtents().getY() * rotationMatrix1[3]
		);

	obb1points[2] = Vector<double>(
		obb1->getPosition().getX() + obb1->getHalfExtents().getX() * rotationMatrix1[0] - obb1->getHalfExtents().getY() * rotationMatrix1[1],
		obb1->getPosition().getY() + obb1->getHalfExtents().getX() * rotationMatrix1[2] - obb1->getHalfExtents().getY() * rotationMatrix1[3]
		);

	obb1points[3] = Vector<double>(
		obb1->getPosition().getX() - obb1->getHalfExtents().getX() * rotationMatrix1[0] - obb1->getHalfExtents().getY() * rotationMatrix1[1],
		obb1->getPosition().getY() - obb1->getHalfExtents().getX() * rotationMatrix1[2] - obb1->getHalfExtents().getY() * rotationMatrix1[3]
		);

	obb2points[0] = Vector<double>(
		obb2->getPosition().getX() - obb2->getHalfExtents().getX() * rotationMatrix2[0] + obb2->getHalfExtents().getY() * rotationMatrix2[1],
		obb2->getPosition().getY() - obb2->getHalfExtents().getX() * rotationMatrix2[2] + obb2->getHalfExtents().getY() * rotationMatrix2[3]
		);

	obb2points[1] = Vector<double>(
		obb2->getPosition().getX() + obb2->getHalfExtents().getX() * rotationMatrix2[0] + obb2->getHalfExtents().getY() * rotationMatrix2[1],
		obb2->getPosition().getY() + obb2->getHalfExtents().getX() * rotationMatrix2[2] + obb2->getHalfExtents().getY() * rotationMatrix2[3]
		);

	obb2points[2] = Vector<double>(
		obb2->getPosition().getX() + obb2->getHalfExtents().getX() * rotationMatrix2[0] - obb2->getHalfExtents().getY() * rotationMatrix2[1],
		obb2->getPosition().getY() + obb2->getHalfExtents().getX() * rotationMatrix2[2] - obb2->getHalfExtents().getY() * rotationMatrix2[3]
		);

	obb2points[3] = Vector<double>(
		obb2->getPosition().getX() - obb2->getHalfExtents().getX() * rotationMatrix2[0] - obb2->getHalfExtents().getY() * rotationMatrix2[1],
		obb2->getPosition().getY() - obb2->getHalfExtents().getX() * rotationMatrix2[2] - obb2->getHalfExtents().getY() * rotationMatrix2[3]
		);

	array<Vector<double>, 4> axis = {
		Vector<double>(rotationMatrix1[0], rotationMatrix1[2]),
		Vector<double>(rotationMatrix1[1], rotationMatrix1[3]),
		Vector<double>(rotationMatrix2[0], rotationMatrix2[2]),
		Vector<double>(rotationMatrix2[1], rotationMatrix2[3])
	};

	for (int j = 0; j < 4; j++)
	{
		double obb1min = 20000000;
		double obb1max = -20000000;

		double obb2min = 20000000;
		double obb2max = -20000000;

		for (int i = 0; i < 4; i++)
		{
			double dotProduct1 = axis[j].dotProduct(&obb1points[i]);
			if (dotProduct1 < obb1min) obb1min = dotProduct1;
			if (dotProduct1 > obb1max) obb1max = dotProduct1;

			double dotProduct2 = axis[j].dotProduct(&obb2points[i]);
			if (dotProduct2 < obb2min) obb2min = dotProduct2;
			if (dotProduct2 > obb2max) obb2max = dotProduct2;

		}
		
		//cout << obb1min << " -- " << obb1max << " -- " << obb2min << " -- " << obb2max << " -- " << (obb1max < obb2min || obb2max < obb1min) << endl;

		if (obb1max < obb2min || obb2max < obb1min) return false;
	}

	cout << "OBB Collision" << endl;
	return true;
	
}


bool Collision::checkCollision(OBB * obb, Circle * circle)
{
	Vector<double> newPosition = circle->getPosition().difference(&obb->getPosition());
	
	Vector <double> inverseRotationMatrixLine1(cos(-obb->getAngle()), -sin(-obb->getAngle()));
	Vector <double> inverseRotationMatrixLine2(sin(-obb->getAngle()), cos(-obb->getAngle()));

	Vector<double> newPosition2(newPosition.dotProduct(&inverseRotationMatrixLine1), newPosition.dotProduct(&inverseRotationMatrixLine2));
	
	Vector<double> dist = newPosition2;
	Vector<double> clamp;
	
	if (dist.getX() < 0) clamp.setX(max(dist.getX(), -obb->getHalfExtents().getX()));
	if (dist.getX() >= 0) clamp.setX(min(dist.getX(), obb->getHalfExtents().getX()));
	if (dist.getY() < 0) clamp.setY(max(dist.getY(), -obb->getHalfExtents().getY()));
	if (dist.getY() >= 0) clamp.setY(min(dist.getY(), obb->getHalfExtents().getY()));

	Vector<double> diff = dist.difference( &clamp );

	if (diff.squaredMagnitude() < std::pow(circle->getRadius(), 2))
	{
		cout << "Circle collision!!" << endl;
		return true;
	}

	return false;
	
}

bool Collision::checkCollision(Circle * circle1, Circle * circle2)
{
	double centreDist = (circle1->getPosition().difference(&circle2->getPosition())).squaredMagnitude();
	double radiiSumSquared = circle1->getRadius()*circle1->getRadius() + circle2->getRadius()*circle2->getRadius();

	return centreDist < radiiSumSquared;
}

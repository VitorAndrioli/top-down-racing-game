/*#include "collision.h"
#include "vector2D.h"
#include <iostream>
#include <array>

using namespace std;

Collision::Collision()
{
}

void Collision::resolveImpulses(Collidable * collidable1, Collidable * collidable2, Vector2D<double> * collisionNormal)
{
	double e = 0.6;

	double j;

	Vector2D<double> va_vb;
	va_vb = collidable1->getVelocity().subtract(&collidable2->getVelocity());

	j = (-(1 + e) * va_vb.dotProduct(collisionNormal)) / (collidable1->getInverseMass() + collidable2->getInverseMass());

	Vector2D<double> newVa = collidable1->getVelocity().add(&collisionNormal->multiplyScalar(j).divideScalar(1 / collidable1->getInverseMass()));
	Vector2D<double> newVb = collidable2->getVelocity().subtract(&collisionNormal->multiplyScalar(j).divideScalar(1 / collidable2->getInverseMass()));

	collidable1->setVelocity(newVa);
	collidable2->setVelocity(newVb);

}

void Collision::checkCollision(Collidable * collidable1, Collidable * collidable2)
{
}

bool Collision::checkCollision(OBB * obb1, OBB * obb2)
{

	array<double, 4> rotationMatrix1 = { cos(obb1->getAngle()), -sin(obb1->getAngle()), sin(obb1->getAngle()), cos(obb1->getAngle()) };
	array<double, 4> rotationMatrix2 = { cos(obb2->getAngle()), -sin(obb2->getAngle()), sin(obb2->getAngle()), cos(obb2->getAngle()) };


	array<Vector2D<double>, 4> obb1points;
	array<Vector2D<double>, 4> obb2points;

	obb1points[0] = Vector2D<double>(
		obb1->getPosition().getX() - obb1->getHalfExtents().getX() * rotationMatrix1[0] + obb1->getHalfExtents().getY() * rotationMatrix1[1],
		obb1->getPosition().getY() - obb1->getHalfExtents().getX() * rotationMatrix1[2] + obb1->getHalfExtents().getY() * rotationMatrix1[3]
		);

	obb1points[1] = Vector2D<double>(
		obb1->getPosition().getX() + obb1->getHalfExtents().getX() * rotationMatrix1[0] + obb1->getHalfExtents().getY() * rotationMatrix1[1],
		obb1->getPosition().getY() + obb1->getHalfExtents().getX() * rotationMatrix1[2] + obb1->getHalfExtents().getY() * rotationMatrix1[3]
		);

	obb1points[2] = Vector2D<double>(
		obb1->getPosition().getX() + obb1->getHalfExtents().getX() * rotationMatrix1[0] - obb1->getHalfExtents().getY() * rotationMatrix1[1],
		obb1->getPosition().getY() + obb1->getHalfExtents().getX() * rotationMatrix1[2] - obb1->getHalfExtents().getY() * rotationMatrix1[3]
		);

	obb1points[3] = Vector2D<double>(
		obb1->getPosition().getX() - obb1->getHalfExtents().getX() * rotationMatrix1[0] - obb1->getHalfExtents().getY() * rotationMatrix1[1],
		obb1->getPosition().getY() - obb1->getHalfExtents().getX() * rotationMatrix1[2] - obb1->getHalfExtents().getY() * rotationMatrix1[3]
		);

	
	obb2points[0] = Vector2D<double>(
		obb2->getPosition().getX() - obb2->getHalfExtents().getX() * rotationMatrix2[0] + obb2->getHalfExtents().getY() * rotationMatrix2[1],
		obb2->getPosition().getY() - obb2->getHalfExtents().getX() * rotationMatrix2[2] + obb2->getHalfExtents().getY() * rotationMatrix2[3]
		);

	obb2points[1] = Vector2D<double>(
		obb2->getPosition().getX() + obb2->getHalfExtents().getX() * rotationMatrix2[0] + obb2->getHalfExtents().getY() * rotationMatrix2[1],
		obb2->getPosition().getY() + obb2->getHalfExtents().getX() * rotationMatrix2[2] + obb2->getHalfExtents().getY() * rotationMatrix2[3]
		);

	obb2points[2] = Vector2D<double>(
		obb2->getPosition().getX() + obb2->getHalfExtents().getX() * rotationMatrix2[0] - obb2->getHalfExtents().getY() * rotationMatrix2[1],
		obb2->getPosition().getY() + obb2->getHalfExtents().getX() * rotationMatrix2[2] - obb2->getHalfExtents().getY() * rotationMatrix2[3]
		);

	obb2points[3] = Vector2D<double>(
		obb2->getPosition().getX() - obb2->getHalfExtents().getX() * rotationMatrix2[0] - obb2->getHalfExtents().getY() * rotationMatrix2[1],
		obb2->getPosition().getY() - obb2->getHalfExtents().getX() * rotationMatrix2[2] - obb2->getHalfExtents().getY() * rotationMatrix2[3]
		);

	array<Vector2D<double>, 4> axis = {
		Vector2D<double>(rotationMatrix1[0], rotationMatrix1[2]),
		Vector2D<double>(rotationMatrix1[1], rotationMatrix1[3]),
		Vector2D<double>(rotationMatrix2[0], rotationMatrix2[2]),
		Vector2D<double>(rotationMatrix2[1], rotationMatrix2[3])
	};

	Vector2D<double> moveVector(99999,99999);
	Vector2D<double> collisionNormal;
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
		
		if (obb1max < obb2min || obb2max < obb1min) return false;

		double overlap1 = obb1max - obb2min;
		double overlap2 = obb2max - obb1min;
		double overlap = min(overlap1, overlap2);


		collisionNormal = axis[j].unitVector();
		Vector2D<double> newVector(collisionNormal.multiplyScalar(-overlap));
		if (newVector.squaredMagnitude() < moveVector.squaredMagnitude()) moveVector = newVector;

	}

	obb1->setPosition(obb1->getPosition().add(&moveVector));

	resolveImpulses(obb1, obb2, &collisionNormal);
	return true;
}


void Collision::checkCollision(OBB * obb, Circle * circle)
{
	Vector2D<double> newPosition = circle->getPosition().subtract(&obb->getPosition());
	
	Vector2D <double> inverseRotationMatrixLine1(cos(-obb->getAngle()), -sin(-obb->getAngle()));
	Vector2D <double> inverseRotationMatrixLine2(sin(-obb->getAngle()), cos(-obb->getAngle()));

	Vector2D<double> newPosition2(newPosition.dotProduct(&inverseRotationMatrixLine1), newPosition.dotProduct(&inverseRotationMatrixLine2));
	
	Vector2D<double> dist = newPosition2;
	Vector2D<double> clamp;
	
	if (dist.getX() < 0) clamp.setX(max(dist.getX(), -obb->getHalfExtents().getX()));
	if (dist.getX() >= 0) clamp.setX(min(dist.getX(), obb->getHalfExtents().getX()));
	if (dist.getY() < 0) clamp.setY(max(dist.getY(), -obb->getHalfExtents().getY()));
	if (dist.getY() >= 0) clamp.setY(min(dist.getY(), obb->getHalfExtents().getY()));

	Vector2D<double> diff = dist.subtract( &clamp );
	double distance = diff.magnitude() - circle->getRadius();

	if (distance < 0)
	{
		Vector2D<double> collisionNormal = (circle->getPosition().subtract(&obb->getPosition().add(&clamp))).unitVector();
		Vector2D<double> moveVector = collisionNormal.multiplyScalar(distance);

		obb->setPosition(obb->getPosition().add(&moveVector));

		resolveImpulses(obb, circle, &collisionNormal);
	}
}

void Collision::checkCollision(Circle * circle1, Circle * circle2)
{
	double centreDist = sqrt( (circle1->getPosition().subtract(&circle2->getPosition())).squaredMagnitude() );
	double radiiSum = circle1->getRadius() + circle2->getRadius();

	double diff = centreDist - radiiSum;

	if (diff < 0)
	{
		
		Vector2D<double> collisionNormal = circle1->getPosition().subtract(&circle2->getPosition()).unitVector();
		Vector2D<double> moveVector = collisionNormal.multiplyScalar(-diff);

		circle1->setPosition(circle1->getPosition().add(&moveVector));

		resolveImpulses(circle1, circle2, &collisionNormal);
	}
}

void Collision::checkCollision(Circle * circle, OBB * obb)
{
	checkCollision(obb, circle);
}
*/
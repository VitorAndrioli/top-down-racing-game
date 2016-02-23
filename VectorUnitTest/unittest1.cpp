#include "stdafx.h"
#include "CppUnitTest.h"
#define _USE_MATH_DEFINES
#include <math.h>

#include "Vector2D.h"
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VectorUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Sum)
		{
			Vector2D<int> vector1(2, 5), vector2(5, 4), vector3(-5, 0), result;
			double iResultX = 7, iResultY = 9;
			result = vector1 + vector2;

			Assert::AreEqual(result.getX(), iResultX);
			Assert::AreEqual(result.getY(), iResultY);

			result = vector1 + vector3;
			iResultX = -3;
			iResultY = 5;
			Assert::AreEqual(result.getX(), iResultX);
			Assert::AreEqual(result.getY(), iResultY);
		}

		TEST_METHOD(Subtraction)
		{
			Vector2D<int> vector1(2, 5), vector2(5, 4), vector3(-5, 0), result;
			double fResultX = -3, fResultY = 1;
			result = vector1 - vector2;
			Assert::AreEqual(result.getX(), fResultX);
			Assert::AreEqual(result.getY(), fResultY);

			result = vector1 - vector3;
			fResultX = 7;
			fResultY = 5;
			Assert::AreEqual(result.getX(), fResultX);
			Assert::AreEqual(result.getY(), fResultY);
		}

		TEST_METHOD(Increment)
		{
			Vector2D<int> vector1(2, 5), vector2(5, 4);
			double iResultX = 7, iResultY = 9;
			vector1 += vector2;

			Assert::AreEqual(vector1.getX(), iResultX);
			Assert::AreEqual(vector1.getY(), iResultY);

			Vector2D<int> vector3(2, 5), vector4(-5, 0);
			iResultX = -3;
			iResultY = 5;
			vector3 += vector4;

			Assert::AreEqual(vector3.getX(), iResultX);
			Assert::AreEqual(vector3.getY(), iResultY);
		}

		TEST_METHOD(Decrement)
		{
			Vector2D<int> vector1(2, 5), vector2(5, 4);
			double iResultX = -3, iResultY = 1;
			vector1 -= vector2;

			Assert::AreEqual(vector1.getX(), iResultX);
			Assert::AreEqual(vector1.getY(), iResultY);

			Vector2D<int> vector3(2, 5), vector4(-5, 0);
			iResultX = 7;
			iResultY = 5;
			vector3 -= vector4;

			Assert::AreEqual(vector3.getX(), iResultX);
			Assert::AreEqual(vector3.getY(), iResultY);
		}

		TEST_METHOD(Multiplication)
		{
			Vector2D<int> vector1(2, 5), result;
			int iScalar = 3;
			double iResultX = 6, iResultY = 15;
			result = vector1 * iScalar;

			Assert::AreEqual(result.getX(), iResultX);
			Assert::AreEqual(result.getY(), iResultY);

			iScalar = -3;
			iResultX = -6;
			iResultY = -15;
			result = vector1 * iScalar;

			Assert::AreEqual(result.getX(), iResultX);
			Assert::AreEqual(result.getY(), iResultY);

			iScalar = 0;
			iResultX = 0;
			iResultY = 0;
			result = vector1 * iScalar;

			Assert::AreEqual(result.getX(), iResultX);
			Assert::AreEqual(result.getY(), iResultY);
		}

		TEST_METHOD(Division)
		{
			Vector2D<int> vector1(12, 15), result;
			int iScalar = 3;
			double iResultX = 4, iResultY = 5;
			result = vector1 / iScalar;

			Assert::AreEqual(result.getX(), iResultX);
			Assert::AreEqual(result.getY(), iResultY);

			iScalar = -3;
			iResultX = -4;
			iResultY = -5;
			result = vector1 / iScalar;

			Assert::AreEqual(result.getX(), iResultX);
			Assert::AreEqual(result.getY(), iResultY);

			iScalar = 0;
			iResultX = 0;
			iResultY = 0;
			result = vector1 / iScalar;

			Assert::AreEqual(result.getX(), iResultX);
			Assert::AreEqual(result.getY(), iResultY);
		}

		TEST_METHOD(Equality)
		{
			Vector2D<int> vector1(12, 15), vector2(12, 15), vector3(12, 14);
			
			Assert::IsTrue(vector1 == vector2);
			Assert::IsFalse(vector1 == vector3);
		}

		TEST_METHOD(Inequality)
		{
			Vector2D<int> vector1(12, 15), vector2(13, 15), vector3(12, 15);

			Assert::IsTrue(vector1 != vector2);
			Assert::IsFalse(vector1 != vector3);
		}

		TEST_METHOD(DotProduct)
		{
			Vector2D<int> vector1(1, 0), vector2(0, 1), vector3(1, 1);

			Assert::AreEqual(vector1.dotProduct(&vector2), 0);
			Assert::AreEqual(vector2.dotProduct(&vector1), 0);
			Assert::AreEqual(vector1.dotProduct(&vector3), 1);
			Assert::AreEqual(vector2.dotProduct(&vector3), 1);

		}

		TEST_METHOD(CrossProduct)
		{
			Vector2D<int> vector1(4, 7), vector2(3, 5);
			
			Assert::AreEqual(vector1.crossProduct(&vector2), -1);
			Assert::AreEqual(vector2.crossProduct(&vector1), 1);
		}
		
		TEST_METHOD(CrossProductScalar)
		{
			Vector2D<int> vector1(1, 1);
			int iScalar1 = 2, iScalar2 = -2;

			Assert::AreEqual(vector1.crossProduct(iScalar1).getX(), 2.0);
			Assert::AreEqual(vector1.crossProduct(iScalar1).getY(), -2.0);
			
			Assert::AreEqual(vector1.crossProduct(iScalar2).getX(), -2.0);
			Assert::AreEqual(vector1.crossProduct(iScalar2).getY(), 2.0);
		}

		TEST_METHOD(Unit)
		{
			Vector2D<int> vector1(57, 0), vector2(-12, 0), vector3(0, 30), vector4(0, -23), vector5(0, 0);

			Assert::AreEqual(vector1.unitVector().getX(), 1.0);
			Assert::AreEqual(vector1.unitVector().getY(), 0.0);
			
			Assert::AreEqual(vector2.unitVector().getX(), -1.0);
			Assert::AreEqual(vector2.unitVector().getY(), 0.0);

			Assert::AreEqual(vector3.unitVector().getX(), 0.0);
			Assert::AreEqual(vector3.unitVector().getY(), 1.0);

			Assert::AreEqual(vector4.unitVector().getX(), 0.0);
			Assert::AreEqual(vector4.unitVector().getY(), -1.0);
			
			Assert::AreEqual(vector5.unitVector().getX(), 0.0);
			Assert::AreEqual(vector5.unitVector().getY(), 0.0);

		}

		TEST_METHOD(Normalize)
		{
			Vector2D<int> vector1(57, 0), vector2(-12, 0), vector3(0, 30), vector4(0, -23), vector5(0, 0);

			vector1.normalize();
			Assert::AreEqual(vector1.getX(), 1.0);
			Assert::AreEqual(vector1.getY(), 0.0);

			vector2.normalize();
			Assert::AreEqual(vector2.getX(), -1.0);
			Assert::AreEqual(vector2.getY(), 0.0);
			
			vector3.normalize();
			Assert::AreEqual(vector3.getX(), 0.0);
			Assert::AreEqual(vector3.getY(), 1.0);
			
			vector4.normalize();
			Assert::AreEqual(vector4.getX(), 0.0);
			Assert::AreEqual(vector4.getY(), -1.0);
			
			vector5.normalize();
			Assert::AreEqual(vector5.getX(), 0.0);
			Assert::AreEqual(vector5.getY(), 0.0);
		}

		TEST_METHOD(Magnitude)
		{
			Vector2D<int> vector1(12, 5), vector2(-12, 5), vector3(12, -5), vector4(-12, -5), vector5(0, 0);

			double result = sqrt(12 * 12 + 5 * 5);
			Assert::AreEqual(vector1.magnitude(), result);
			
			result = sqrt((-12) * (-12) + 5 * 5);
			Assert::AreEqual(vector2.magnitude(), result);
			
			result = sqrt(12 * 12 + (-5) * (-5));
			Assert::AreEqual(vector3.magnitude(), result);
			
			result = sqrt((-12) * (-12) + (-5) * (-5));
			Assert::AreEqual(vector4.magnitude(), result);
			
			result = 0;
			Assert::AreEqual(vector5.magnitude(), result);
			
		}

		TEST_METHOD(SquaredMagnitude)
		{
			Vector2D<int> vector1(12, 5), vector2(-12, 5), vector3(12, -5), vector4(-12, -5), vector5(0, 0);

			double result = 12 * 12 + 5 * 5;
			Assert::AreEqual(vector1.squaredMagnitude(), result);

			result = (-12) * (-12) + 5 * 5;
			Assert::AreEqual(vector2.squaredMagnitude(), result);

			result = 12 * 12 + (-5) * (-5);
			Assert::AreEqual(vector3.squaredMagnitude(), result);

			result = (-12) * (-12) + (-5) * (-5);
			Assert::AreEqual(vector4.squaredMagnitude(), result);

			result = 0;
			Assert::AreEqual(vector5.squaredMagnitude(), result);
		}

		TEST_METHOD(Rotate)
		{
			Vector2D<int> vector1(1, 0);

			vector1.rotate(90 * M_PI / 180);
			Assert::AreEqual(vector1.getX(), 0.0);
			Assert::AreEqual(vector1.getY(), 1.0);

			vector1.rotate(90 * M_PI / 180);
			Assert::AreEqual(vector1.getX(), -1.0);
			Assert::AreEqual(vector1.getY(), 0.0);

			vector1.rotate(90 * M_PI / 180);
			Assert::AreEqual(vector1.getX(), 0.0);
			Assert::AreEqual(vector1.getY(), -1.0);

			vector1.rotate(90 * M_PI / 180);
			Assert::AreEqual(vector1.getX(), 1.0);
			Assert::AreEqual(vector1.getY(), 0.0);
		}

		TEST_METHOD(Flip)
		{
			Vector2D<int> vector1(5, 5);

			vector1.flip();
			Assert::AreEqual(vector1.getX(), -5.0);
			Assert::AreEqual(vector1.getY(), -5.0);

			Vector2D<int> vector2(-5, 5);

			vector2.flip();
			Assert::AreEqual(vector2.getX(), 5.0);
			Assert::AreEqual(vector2.getY(), -5.0);

			Vector2D<int> vector3(5, -5);

			vector3.flip();
			Assert::AreEqual(vector3.getX(), -5.0);
			Assert::AreEqual(vector3.getY(), 5.0);

			Vector2D<int> vector4(-5, -5);

			vector4.flip();
			Assert::AreEqual(vector4.getX(), 5.0);
			Assert::AreEqual(vector4.getY(), 5.0);
			
		}

	};
}
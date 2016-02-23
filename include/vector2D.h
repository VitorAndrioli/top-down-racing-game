/*!
* \file
* \brief Declaration and implementation of templated Vector2D class.
*/

/*!
 * \class Vector2D
 *
 * \brief 2D vectors templated class.
 *
 * Implements 2D vectors arithmetics and manipulation.
 *
 */

#ifndef VECTOR_H
#define VECTOR_H

template <class G>
class Vector2D
{
public:
	Vector2D(); //!< Default constructor that creates an empty vector.
	Vector2D(G x, G y); //!< Constructor that creates a vector with X and Y values.
	G dotProduct(Vector2D<G>* pOtherVector); //!< Calculates dot product with another vector.
	G crossProduct(Vector2D<G>* pOtherVector); //!< Calculates cross product with another vector.
	Vector2D<G> crossProduct(double fScalar); //!< Calculates cross product with a scalar.
	Vector2D<G> unitVector(); //!< Gets unitary vector.
	void normalize(); //!< Turns into unitary vector.
	double squaredMagnitude(); //!< Gets squared magnitude.
	double magnitude(); //!< Gets magnitude.
	void rotate(double fAngle); //!< Rotates the vector.
	void flip(); //!< Flips vector in both axes.
	
	// Setters and getters.
	double getX();
	double getY();
	double getOrientation();
	void setX(G x);
	void setY(G y);

	// Ovreload operators.
	Vector2D<G> operator+ (Vector2D<G>& pOtherVector); //!< Overloads + operand (Sum with a vector)
	Vector2D<G> operator- (Vector2D<G>& pOtherVector); //!< Overloads - operand (Subtraction with a vector)
	void operator+= (Vector2D<G>& pOtherVector); //!< Overloads += operand (Increment of a vector)
	void operator-= (Vector2D<G>& pOtherVector); //!< Overloads -= operand (Decrement of a vector)
	Vector2D<G> operator* (double fScalar); //!< Overloads * operand (Multiplication by a scalar)
	Vector2D<G> operator/ (double fScalar); //!< Overloads / operand (Division by a scalar)
	bool operator== (Vector2D<G>& pOtherVector); //!< Overloads == operand (Comparison with a vector)
	bool operator!= (Vector2D<G>& pOtherVector); //!< Overloads != operand (Comparison with a vector)

private:
	G m_x; //!< X value of the vector
	G m_y; //!< Y value of the vector
};

template <class G>
Vector2D<G>::Vector2D()
{
	m_x = 0;
	m_y = 0;
}

/*!
 * \param x,y Coordinates for the vector.
 */
template <class G>
Vector2D<G>::Vector2D(G x, G y)
{
	m_x = x;
	m_y = y;
}

/*!
 * \param pOtherVector Pointer to another Vector2D object.
 *
 * \return Dot product.
 */
template <class G>
G Vector2D<G>::dotProduct(Vector2D<G>* pOtherVector)
{
	return m_x * pOtherVector->getX() + m_y * pOtherVector->getY();
}

/*!
 * There is no cross product defined for 2D vectors. We can, however, make some abstractions:
 * Cross product between two vectors is a scalar, that represents 
 * the magnitude in the non existent Z axis (were these 3D vectors).
 *
 * \param pOtherVector Pointer to another Vector2D object.
 *
 * \return Scalar cross product.
 */
template <class G>
G Vector2D<G>::crossProduct(Vector2D<G>* pOtherVector)
{
	return m_x * pOtherVector->getY() - m_y * pOtherVector->getX();
}

/*!
 * There is no cross product defined for 2D vectors. We can, however, make some abstractions:
 * Cross product between a vector and a scalar (representing the magnitude in the non existent Z axis were these 3D vectors),
 * is a 2D vector.
 *
 * \param fScalar Scalar value
 *
 * \return 2D vector.
 */
template <class G>
Vector2D<G> Vector2D<G>::crossProduct(double fScalar)
{
	return Vector2D<G>(fScalar * m_y, -fScalar * m_x);
}

template<class G>
Vector2D<G> Vector2D<G>::unitVector()
{
	double fMagnitude = magnitude();
	if (fMagnitude == 0) return Vector2D<G>(0, 0);

	G x = m_x / fMagnitude;
	G y = m_y / fMagnitude;
	return Vector2D<G>(x, y);
}

/*!
 * Used to avoid calling sqrt() functions.
 */
template <class G>
double Vector2D<G>::squaredMagnitude()
{
	return dotProduct(this);
}

template <class G>
double Vector2D<G>::magnitude()
{
	return sqrt(squaredMagnitude());
}

/*!
 * \param fAngle Angle by which the vector must be rotated.
 */
template <class G>
void Vector2D<G>::rotate(double fAngle)
{
	G tempX = m_x;
	G tempY = m_y;

	m_x = cos(fAngle)*tempX - sin(fAngle)*tempY;
	m_y = sin(fAngle)*tempX + cos(fAngle)*tempY;
}

template <class G>
void Vector2D<G>::flip()
{
	m_x = -m_x;
	m_y = -m_y;
}

template <class G>
void Vector2D<G>::normalize()
{
	double fMagnitude = magnitude();
	if (fMagnitude == 0)
	{
		m_x = 0;
		m_y = 0;
	}
	else
	{
		G newX = m_x / fMagnitude;
		G newY = m_y / fMagnitude;
		m_x = newX;
		m_y = newY;
	}
}

// Setters and getters.
template <class G>
void Vector2D<G>::setX(G x)
{
	m_x = x;
}

template <class G>
void Vector2D<G>::setY(G y)
{
	m_y = y;
}

template <class G>
double Vector2D<G>::getX()
{
	return m_x;
}

template <class G>
double Vector2D<G>::getY()
{
	return m_y;
}

template <class G>
double Vector2D<G>::getOrientation()
{
	if (squaredMagnitude() == 0) return 0;
	double fOrientation = acos(m_x / magnitude());
	if (m_y < 0) fOrientation *= -1;
	return fOrientation;
}



// Operators override
template <class G>
Vector2D<G> Vector2D<G>::operator+(Vector2D<G>& otherVector)
{
	G x = m_x + otherVector.getX();
	G y = m_y + otherVector.getY();
	return Vector2D<G>(x, y);
}

template <class G>
Vector2D<G> Vector2D<G>::operator-(Vector2D<G>& otherVector)
{
	G x = m_x - otherVector.getX();
	G y = m_y - otherVector.getY();
	return Vector2D<G>(x, y);
}

template <class G>
Vector2D<G> Vector2D<G>::operator*(double scalar)
{
	G x = m_x * scalar;
	G y = m_y * scalar;
	return Vector2D<G>(x, y);
}

template <class G>
Vector2D<G> Vector2D<G>::operator/(double scalar)
{
	if (scalar == 0) return Vector2D<G>(0, 0);
	G x = m_x / scalar;
	G y = m_y / scalar;
	return Vector2D<G>(x, y);
}

template <class G>
void Vector2D<G>::operator+=(Vector2D<G>& otherVector)
{
	m_x = m_x + otherVector.getX();
	m_y = m_y + otherVector.getY();
}

template <class G>
void Vector2D<G>::operator-=(Vector2D<G>& otherVector)
{
	m_x = m_x - otherVector.getX();
	m_y = m_y - otherVector.getY();
}

template <class G>
bool Vector2D<G>::operator== (Vector2D<G>& otherVector)
{
	return m_x == otherVector.getX() && m_y == otherVector.getY();
}

template <class G>
bool Vector2D<G>::operator!= (Vector2D<G>& otherVector)
{
	return m_x != otherVector.getX() || m_y != otherVector.getY();
}

#endif
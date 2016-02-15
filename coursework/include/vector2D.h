//! \file vector2D.h Declaration of Vector2D class.

/*!
* \class Vector2D
*
*
* \brief Small text that appears on Classes page.
*
* Longer text that appears on
* description section
*
*
*/

#ifndef VECTOR_H
#define VECTOR_H

template <class G>
class Vector2D
{
private:
	G m_x; //!< X value of the vector
	G m_y; //!< Y value of the vector
public:
	Vector2D(); //!< Basic constructor that creates an empty vector
	Vector2D(G x, G y); //!< Constructor that creates and vector with X and Y values
	double dotProduct(Vector2D<G> * vector2d); //!< Calculates the dot product of this vector with another one received by reference as a paremeter
	double crossProduct(Vector2D<G> * vector2d);
	Vector2D<G> crossProduct(double fScalar);
	Vector2D<G> unitVector(); //!<
	double squaredMagnitude(); //!<
	double magnitude(); //!<
	void rotate(double fAngle); //!<
	void flip();
	void normalize();
	G getX();
	G getY();
	void setX(G x);
	void setY(G y);

	Vector2D<G> operator+ (Vector2D<G>& other);
	Vector2D<G> operator- (Vector2D<G>& other);
	void operator+= (Vector2D<G>& other);
	void operator-= (Vector2D<G>& other);
	Vector2D<G> operator* (double scalar);
	Vector2D<G> operator/ (double scalar);
};

template <class G>
Vector2D<G>::Vector2D()
{
	m_x = 0;
	m_y = 0;
}

template <class G>
Vector2D<G>::Vector2D(G x, G y)
{
	m_x = x;
	m_y = y;
}

template <class G>
double Vector2D<G>::dotProduct(Vector2D<G> * vector2d)
{
	return m_x * vector2d->getX() + m_y * vector2d->getY();
}

template <class G>
double Vector2D<G>::crossProduct(Vector2D<G> * vector2d)
{
	return m_x * vector2d->getY() - m_y * vector2d->getX();
}

template <class G>
Vector2D<G> Vector2D<G>::crossProduct(double fScalar)
{
	return Vector2D<G>(fScalar * m_y, -fScalar * m_x);
}

template<class G>
Vector2D<G> Vector2D<G>::unitVector()
{
	G x = m_x / magnitude();
	G y = m_y / magnitude();
	return Vector2D<G>(x, y);
}

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
	G newX = m_x / magnitude();
	G newY = m_y / magnitude();
	m_x = newX;
	m_y = newY;
}

template <class G>
G Vector2D<G>::getX()
{
	return m_x;
}

template <class G>
G Vector2D<G>::getY()
{
	return m_y;
}

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
Vector2D<G> Vector2D<G>::operator+(Vector2D<G>& other)
{
	G x = m_x + other.getX();
	G y = m_y + other.getY();
	return Vector2D<G>(x, y);
}

template <class G>
Vector2D<G> Vector2D<G>::operator-(Vector2D<G>& other)
{
	G x = m_x - other.getX();
	G y = m_y - other.getY();
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
	G x = m_x / scalar;
	G y = m_y / scalar;
	return Vector2D<G>(x, y);
}

template <class G>
void Vector2D<G>::operator+=(Vector2D<G>& other)
{
	m_x = m_x + other.getX();
	m_y = m_y + other.getY();
}

template <class G>
void Vector2D<G>::operator-=(Vector2D<G>& other)
{
	m_x = m_x - other.getX();
	m_y = m_y - other.getY();
}

#endif
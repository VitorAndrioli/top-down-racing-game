/**
@file vector2D.h

@brief Brief explanation


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
	Vector2D<G> subtract(Vector2D<G> * vector2d); //!< 
	Vector2D<G> add(Vector2D<G> * vector2d); //!<
	Vector2D<G> multiplyScalar(double fScalar); //!<
	Vector2D<G> divideScalar(double fScalar); //!<
	Vector2D<G> unitVector(); //!<
	double squaredMagnitude(); //!<
	double magnitude(); //!<
	void rotate(double fAngle); //!<
	G getX();
	G getY();
	void setX(G x);
	void setY(G y);
};

template <class G>
Vector2D<G>::Vector2D()
{

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
Vector2D<G> Vector2D<G>::subtract(Vector2D<G> * vector2d)
{
	G x = m_x - vector2d->getX();
	G y = m_y - vector2d->getY();
	return Vector2D<G>(x, y);
}

template <class G>
Vector2D<G> Vector2D<G>::add(Vector2D<G> * vector2d)
{
	G x = m_x + vector2d->getX();
	G y = m_y + vector2d->getY();
	return Vector2D<G>(x, y);
}

template<class G>
Vector2D<G> Vector2D<G>::multiplyScalar(double dScalar)
{
	return Vector2D<double>(m_x * dScalar, m_y * dScalar);
}

template<class G>
Vector2D<G> Vector2D<G>::divideScalar(double dScalar)
{
	return Vector2D<double>(m_x / dScalar, m_y / dScalar);
}

template<class G>
Vector2D<G> Vector2D<G>::unitVector()
{
	double x = m_x / magnitude();
	double y = m_y / magnitude();
	return Vector2D<G>(x, y);
}

template <class G>
double Vector2D<G>::squaredMagnitude()
{
	dotProduct(this);
	return m_x * m_x + m_y * m_y;
}

template <class G>
double Vector2D<G>::magnitude()
{
	return sqrt(squaredMagnitude());
}

template <class G>
void Vector2D<G>::rotate(double fAngle)
{
	Vector2D<Vector2D<double>> rotationMatrix(
		Vector2D<double>(cos(fAngle), -sin(fAngle)),
		Vector2D<double>(sin(fAngle), cos(fAngle)));

	m_x = this->dotProduct(&rotationMatrix.getX());
	m_y = this->dotProduct(&rotationMatrix.getY());
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

#endif
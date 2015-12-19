#ifndef VECTOR_H
#define VECTOR_H

template <class G>
class Vector2D
{
private:
	G m_dX;
	G m_dY;
public:
	Vector2D();
	Vector2D(G x, G y);
	double dotProduct(Vector2D<G> * vector2d);
	Vector2D<G> subtract(Vector2D<G> * vector2d);
	Vector2D<G> add(Vector2D<G> * vector2d);
	Vector2D<G> multiplyScalar(double dScalar);
	Vector2D<G> divideScalar(double dScalar);
	double squaredMagnitude();
	double magnitude();
	void rotate(double dAngle);
	G getX();
	G getY();
	void setX(G x);
	void setY(G y);
};

template <class G>
Vector2D<G>::Vector2D<G>()
{

}

template <class G>
Vector2D<G>::Vector2D(G x, G y)
{
	m_dX = x;
	m_dY = y;
}

template <class G>
double Vector2D<G>::dotProduct(Vector2D<G> * vector2d)
{
	return m_dX*vector2d->getX() + m_dY*vector2d->getY();
}

template <class G>
Vector2D<G> Vector2D<G>::subtract(Vector2D<G> * vector2d)
{
	G x = m_dX - vector2d->getX();
	G y = m_dY - vector2d->getY();
	return Vector2D<G>(x, y);
}

template <class G>
Vector2D<G> Vector2D<G>::add(Vector2D<G> * vector2d)
{
	G x = m_dX + vector2d->getX();
	G y = m_dY + vector2d->getY();
	return Vector2D<G>(x, y);
}

template<class G>
Vector2D<G> Vector2D<G>::multiplyScalar(double dScalar)
{
	return Vector2D<double>(m_dX*dScalar, m_dY*dScalar);
}

template<class G>
Vector2D<G> Vector2D<G>::divideScalar(double dScalar)
{
	return Vector2D<double>(m_dX / dScalar, m_dY / dScalar);
}

template <class G>
double Vector2D<G>::squaredMagnitude()
{
	return m_dX*m_dX + m_dY*m_dY;
}

template <class G>
double Vector2D<G>::magnitude()
{
	return sqrt(m_dX*m_dX + m_dY*m_dY);
}

template <class G>
void Vector2D<G>::rotate(double dAngle)
{
	Vector2D<Vector2D<double>> rotationMatrix(
		Vector2D<double>(cos(dAngle), -sin(dAngle)),
		Vector2D<double>(sin(dAngle), cos(dAngle)));

	m_dX = this->dotProduct(&rotationMatrix[0]);
	m_dY = this->dotProduct(&rotationMatrix[1]);
}

template <class G>
G Vector2D<G>::getX()
{
	return m_dX;
}

template <class G>
G Vector2D<G>::getY()
{
	return m_dY;
}

template <class G>
void Vector2D<G>::setX(G x)
{
	m_dX = x;
}

template <class G>
void Vector2D<G>::setY(G y)
{
	m_dY = y;
}

#endif
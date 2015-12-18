#ifndef VECTOR_H
#define VECTOR_H

template <class G>
class Vector
{
private:
	G m_dX;
	G m_dY;
public:
	Vector();
	Vector(G x, G y);
	double dotProduct(Vector<G> * vector);
	Vector<G> difference(Vector<G> * vector);
	Vector<G> sum(Vector<G> * vector);
	Vector<G> multiply(double x);
	Vector<G> divide(double x);
	double squaredMagnitude();
	G getX();
	G getY();
	void setX(G x);
	void setY(G y);
};

template<class G>
Vector<G>::Vector()
{

}

template <class G>
Vector<G>::Vector(G x, G y)
{
	m_dX = x;
	m_dY = y;
}

template<class G>
Vector<G> Vector<G>::multiply(double x)
{
	return Vector<double>(m_dX*x, m_dY*x);
}

template<class G>
Vector<G> Vector<G>::divide(double x)
{
	return Vector<double>(m_dX/x, m_dY/x);
}

template <class G>
double Vector<G>::dotProduct(Vector<G> * vector)
{
	return m_dX*vector->getX() + m_dY*vector->getY();
}

template <class G>
Vector<G> Vector<G>::difference(Vector<G> * vector)
{
	G x = m_dX - vector->getX();
	G y = m_dY - vector->getY();
	return Vector<G>(x, y);
}

template <class G>
Vector<G> Vector<G>::sum(Vector<G> * vector)
{
	G x = m_dX + vector->getX();
	G y = m_dY + vector->getY();
	return Vector<G>(x, y);
}

template <class G>
double Vector<G>::squaredMagnitude()
{
	return m_dX*m_dX + m_dY*m_dY;
}

template <class G>
G Vector<G>::getX()
{
	return m_dX;
}

template <class G>
G Vector<G>::getY()
{
	return m_dY;
}

template <class G>
void Vector<G>::setX(G x)
{
	m_dX = x;
}

template <class G>
void Vector<G>::setY(G y)
{
	m_dY = y;
}

#endif
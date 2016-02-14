#include "tyre.h"
#include "vector2D.h"


Tyre::Tyre(double fPosX, double fPosY, double fOrientation)
{
	m_fvPosition = Vector2D<double>(fPosX, fPosY);
	m_fRadius = 10;
	m_fOrientation = fOrientation;
	m_fInverseMass = 1.f / (m_fRadius * 2.f);
}

Tyre::Tyre()
{
}

Tyre::~Tyre()
{
}

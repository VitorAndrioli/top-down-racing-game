#include "obb.h"
#include "circle.h"
#include "SFML\Graphics.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <array>

using namespace std;

OBB::OBB()
{

}

OBB::OBB(double fPosX, double fPosY, double fHalfExtentX, double fHalfExtentY, double fOrientation)
{
	m_fvHalfExtents = Vector2D<double>(fHalfExtentX, fHalfExtentY);
	m_fvPosition = Vector2D<double>(fPosX, fPosY);
		
	m_fOrientation = fOrientation;
	setMass(fHalfExtentX*fHalfExtentY);
	m_fRadius = m_fvHalfExtents.magnitude();
	m_fElasticity = 0.6;

	//m_fInverseMomentOfInertia = (getMass() * (dHalfExtentX*dHalfExtentX + dHalfExtentY*dHalfExtentY))/12;

	m_vaPoints.resize(5);
}

void OBB::updatePoints()
{
	
	/*Vector2D<double> rotationMatrixLine1(cos(m_fOrientation), -sin(m_fOrientation));
	Vector2D<double> rotationMatrixLine2(sin(m_fOrientation), cos(m_fOrientation));

	Vector2D<double> tempVector(-m_fvHalfExtents.getX(), m_fvHalfExtents.getY());
	tempVector.rotate(m_fOrientation);
	m_vaPoints[0].position.x = m_vaPoints[4].position.x = (tempVector + getPosition()).getX();
	m_vaPoints[0].position.y = m_vaPoints[4].position.y = (tempVector + getPosition()).getY();

	tempVector = Vector2D<double>(m_fvHalfExtents.getX(), m_fvHalfExtents.getY());
	tempVector.rotate(m_fOrientation);
	m_vaPoints[1].position.x = (tempVector + getPosition()).getX();
	m_vaPoints[1].position.y = (tempVector + getPosition()).getY();

	tempVector = Vector2D<double>(m_fvHalfExtents.getX(), -m_fvHalfExtents.getY());
	tempVector.rotate(m_fOrientation);
	m_vaPoints[2].position.x = (tempVector + getPosition()).getX();
	m_vaPoints[2].position.y = (tempVector + getPosition()).getY();

	tempVector = Vector2D<double>(-m_fvHalfExtents.getX(), -m_fvHalfExtents.getY());
	tempVector.rotate(m_fOrientation);
	m_vaPoints[3].position.x = (tempVector + getPosition()).getX();
	m_vaPoints[3].position.y = (tempVector + getPosition()).getY();*/

}

void OBB::checkCollision(Collidable * collidable)
{
	collidable->checkCollision(this);
}

void OBB::checkCollision(Circle * circle)
{
	if (!broadCollisionCheck(circle)) return;

	Vector2D<double> fvCentreDistance = circle->getPosition() - m_fvPosition;
	fvCentreDistance.rotate(-m_fOrientation);

	Vector2D<double> fvClamp;
	if (fvCentreDistance.getX() < 0) fvClamp.setX(std::max(fvCentreDistance.getX(), -m_fvHalfExtents.getX()));
	if (fvCentreDistance.getX() >= 0) fvClamp.setX(std::min(fvCentreDistance.getX(), m_fvHalfExtents.getX()));
	if (fvCentreDistance.getY() < 0) fvClamp.setY(std::max(fvCentreDistance.getY(), -m_fvHalfExtents.getY()));
	if (fvCentreDistance.getY() >= 0) fvClamp.setY(std::min(fvCentreDistance.getY(), m_fvHalfExtents.getY()));
	

	Vector2D<double> fvDiff = fvCentreDistance - fvClamp;
	if (fvDiff.squaredMagnitude() < (circle->getRadius()*circle->getRadius()))
	{
		double fOverlap = fvDiff.magnitude() - circle->getRadius();
		
		fvClamp.rotate(m_fOrientation);
		Vector2D<double> fvCollisionNormal = fvClamp + m_fvPosition - circle->getPosition();
		fvCollisionNormal.normalize();
		resolveCollision(circle, &fvCollisionNormal, fOverlap);

	}
}

void OBB::checkCollision(OBB * obb)
{
	if (!broadCollisionCheck(obb)) return;

	array<Vector2D<double>, 4> obb1points;
	array<Vector2D<double>, 4> obb2points;

	obb1points[0] = Vector2D<double>(m_fvHalfExtents.getX(), m_fvHalfExtents.getY());
	obb1points[1] = Vector2D<double>(m_fvHalfExtents.getX(), -m_fvHalfExtents.getY());
	obb1points[2] = Vector2D<double>(-m_fvHalfExtents.getX(), m_fvHalfExtents.getY());
	obb1points[3] = Vector2D<double>(-m_fvHalfExtents.getX(), -m_fvHalfExtents.getY());
	for (auto it = obb1points.begin(); it != obb1points.end(); ++it)
	{
		(*it).rotate(m_fOrientation);
		(*it) += m_fvPosition;
	}

	obb2points[0] = Vector2D<double>(obb->getHalfExtents().getX(), obb->getHalfExtents().getY());
	obb2points[1] = Vector2D<double>(obb->getHalfExtents().getX(), -obb->getHalfExtents().getY());
	obb2points[2] = Vector2D<double>(-obb->getHalfExtents().getX(), obb->getHalfExtents().getY());
	obb2points[3] = Vector2D<double>(-obb->getHalfExtents().getX(), -obb->getHalfExtents().getY());
	for (auto it = obb2points.begin(); it != obb2points.end(); ++it)
	{
		(*it).rotate(obb->getOrientation());
		(*it) += obb->getPosition();
	}

	array<Vector2D<double>, 4> axis = {
		Vector2D<double>(cos(m_fOrientation), sin(m_fOrientation)),
		Vector2D<double>(-sin(m_fOrientation), cos(m_fOrientation)),
		Vector2D<double>(cos(obb->getOrientation()), sin(obb->getOrientation())),
		Vector2D<double>(-sin(obb->getOrientation()), cos(obb->getOrientation()))
	};

	Vector2D<double> fvCollisionNormal;
	double finalOverlap = 999999;
	bool flip = false;

	for (auto it = axis.begin(); it != axis.end(); ++it)
	{
		double obb1min = 20000000;
		double obb1max = -20000000;

		double obb2min = 20000000;
		double obb2max = -20000000;

		for (int j = 0; j < 4; j++)
		{
			double dotProduct1 = (*it).dotProduct(&obb1points[j]);
			if (dotProduct1 < obb1min) obb1min = dotProduct1;
			if (dotProduct1 > obb1max) obb1max = dotProduct1;

			double dotProduct2 = (*it).dotProduct(&obb2points[j]);
			if (dotProduct2 < obb2min) obb2min = dotProduct2;
			if (dotProduct2 > obb2max) obb2max = dotProduct2;
		}

		if (obb1max < obb2min || obb2max < obb1min) return;
		
		double overlap1 = obb1max - obb2min;
		double overlap2 = obb2max - obb1min;
		double overlap = min(overlap1, overlap2);

		if (overlap < finalOverlap)
		{
			fvCollisionNormal = (*it).unitVector();
			finalOverlap = overlap;
		}
				
	}
	
	Vector2D<double> relativePosition = m_fvPosition - obb->getPosition();
	if (relativePosition.dotProduct(&fvCollisionNormal) < 0) fvCollisionNormal.flip();

	//std::cout << collisionNormal.getX() << " | " << collisionNormal.getY() << " | " << (getPosition() - obb->getPosition()).dotProduct(&collisionNormal) << endl;
	resolveCollision(obb, &fvCollisionNormal, -finalOverlap);
	
}

void OBB::setTexture(sf::Texture * texture)
{
	m_sprite.setTexture(*texture);
	m_sprite.setOrigin(texture->getSize().x / 2, texture->getSize().y/2);
	//m_sprite.setTextureRect(sf::IntRect(0, 0, m_fvHalfExtents.getX() * 2, m_fvHalfExtents.getY() * 2));
	m_sprite.scale(m_fvHalfExtents.getX() * 2 / texture->getSize().x, m_fvHalfExtents.getY() * 2 / texture->getSize().y);
	//m_sprite.setColor(sf::Color(255, 255, 255, 128));

}


Vector2D<double> OBB::getHalfExtents()
{
	return m_fvHalfExtents;
}


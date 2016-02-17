//! \file collidableFactory.cpp Implementation of CollidableFactory class.

#include "collidableFactory.h"

Collidable * CollidableFactory::NewCollidable(const rapidxml::xml_node<>* pNode, TextureManager * textureManager)
{

	string sCollidableType = pNode->first_attribute("type")->value();

	if (sCollidableType == "obb")
	{
		double fPosX = atof(pNode->first_attribute("posX")->value());
		double fPosY = atof(pNode->first_attribute("posY")->value());
		double fHalfExtentX = atof(pNode->first_attribute("halfExtentX")->value());
		double fHalfExtentY = atof(pNode->first_attribute("halfExtentY")->value());
		double fOrientation = atof(pNode->first_attribute("orientation")->value());
		
		OBB * obb = new OBB(fPosX, fPosY, fHalfExtentX, fHalfExtentY, fOrientation * 3.14159 / 180);
		obb->setTexture(&(textureManager->m_aTexture.at(6)));
		return obb;
	}
	if (sCollidableType == "circle")
	{
		double fPosX = atof(pNode->first_attribute("posX")->value());
		double fPosY = atof(pNode->first_attribute("posY")->value());
		double fRadius = atof(pNode->first_attribute("radius")->value());
		
		return new Circle(fPosX, fPosY, fRadius);
	}
	if (sCollidableType == "tyre")
	{
		double fPosX = atof(pNode->first_attribute("posX")->value());
		double fPosY = atof(pNode->first_attribute("posY")->value());
		
		Tyre * tyre = new Tyre(fPosX, fPosY);
		tyre->setTexture(&(textureManager->m_aTexture.at(5)));
		
		return tyre;
	}
	if (sCollidableType == "box")
	{
		double fPosX = atof(pNode->first_attribute("posX")->value());
		double fPosY = atof(pNode->first_attribute("posY")->value());
		double fSize = atof(pNode->first_attribute("size")->value());
		double fOrientation = atof(pNode->first_attribute("orientation")->value());

		Box * box = new Box(fPosX, fPosY, fSize, fOrientation * 3.14159 / 180);
		box->setTexture(&(textureManager->m_aTexture.at(6)));
		return box;
	}
	return NULL;

}


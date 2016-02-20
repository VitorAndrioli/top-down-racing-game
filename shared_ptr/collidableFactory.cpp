//! \file collidableFactory.cpp Implementation of CollidableFactory class.

#include "collidableFactory.h"

shared_ptr<Collidable> CollidableFactory::generateCollidable(const rapidxml::xml_node<>* pNode)
{
	shared_ptr<Collidable> pCollidable;
	pCollidable = makeCollidable(pNode);

	return pCollidable;
}

shared_ptr<Collidable> CollidableFactory::makeCollidable(const rapidxml::xml_node<>* pNode)
{
	TextureManager *textureManager = TextureManager::getInstance();
	string sCollidableType = pNode->first_attribute("type")->value();

	if (sCollidableType == "obb")
	{
		double fPosX = atof(pNode->first_attribute("posX")->value());
		double fPosY = atof(pNode->first_attribute("posY")->value());
		double fHalfExtentX = atof(pNode->first_attribute("halfExtentX")->value());
		double fHalfExtentY = atof(pNode->first_attribute("halfExtentY")->value());
		double fOrientation = atof(pNode->first_attribute("orientation")->value());

		shared_ptr<Collidable> pCollidable(new OBB(fPosX, fPosY, fHalfExtentX, fHalfExtentY, fOrientation * 3.14159 / 180));
		return pCollidable;
	}
	if (sCollidableType == "circle")
	{
		double fPosX = atof(pNode->first_attribute("posX")->value());
		double fPosY = atof(pNode->first_attribute("posY")->value());
		double fRadius = atof(pNode->first_attribute("radius")->value());

		shared_ptr<Collidable> pCollidable(new Circle(fPosX, fPosY, fRadius));
		return pCollidable;
	}
	if (sCollidableType == "tyre")
	{
		double fPosX = atof(pNode->first_attribute("posX")->value());
		double fPosY = atof(pNode->first_attribute("posY")->value());

		shared_ptr<Collidable> pCollidable(new Tyre(fPosX, fPosY));
		pCollidable->setTexture(textureManager->getTexturePointer(sCollidableType));
		return pCollidable;
	}
	if (sCollidableType == "box")
	{
		double fPosX = atof(pNode->first_attribute("posX")->value());
		double fPosY = atof(pNode->first_attribute("posY")->value());
		double fSize = atof(pNode->first_attribute("size")->value());
		double fOrientation = atof(pNode->first_attribute("orientation")->value());

		shared_ptr<Collidable> pCollidable(new Box(fPosX, fPosY, fSize, fOrientation * 3.14159 / 180));
		pCollidable->setTexture(textureManager->getTexturePointer(sCollidableType));
		return pCollidable;
	}
	return nullptr;
}


#include "carDisplay.h"


CarDisplay::CarDisplay()
{
}

CarDisplay::CarDisplay(double fMaximumSpeedSquared) : m_fMaximumSpeedSquared(fMaximumSpeedSquared)
{
	TextureManager* textureManager = TextureManager::getInstance();

	m_velocimeter.setTexture(*textureManager->getTexturePointer("velocimeter"));
	//m_velocimeter.setOrigin(m_velocimeter.getTexture()->getSize().x / 2, m_velocimeter.getTexture()->getSize().y / 2); // Sets sprite's center as its origin (instead of its corner).
	m_velocimeter.scale(100.f / m_velocimeter.getTexture()->getSize().x, 100.f / m_velocimeter.getTexture()->getSize().y); // Scales texture to make sure it fits the car.


	m_velocimeterPointer.setTexture(*textureManager->getTexturePointer("pointer"));
	m_velocimeterPointer.setOrigin(m_velocimeterPointer.getTexture()->getSize().x / 2, m_velocimeterPointer.getTexture()->getSize().y / 2); // Sets sprite's center as its origin (instead of its corner).
	m_velocimeterPointer.scale(100.f / m_velocimeterPointer.getTexture()->getSize().x, 100.f / m_velocimeterPointer.getTexture()->getSize().y); // Scales texture to make sure it fits the car.
	m_velocimeterPointer.setPosition(50, 50);
}

void CarDisplay::update(double fSpeedSquared)
{
	double orientation = fSpeedSquared * MAXIMUM_ROTATION / m_fMaximumSpeedSquared;
	m_velocimeterPointer.setRotation(orientation);
}


void CarDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Draw sprite of the car and of the front wheels.
	target.draw(m_velocimeter);
	target.draw(m_velocimeterPointer);
}



CarDisplay::~CarDisplay()
{
}

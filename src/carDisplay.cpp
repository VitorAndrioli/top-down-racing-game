/*!
 * \file
 * \brief Implementation of CarDisplay class.
 */

#include "carDisplay.h"

CarDisplay::CarDisplay()
{
}

/*!
 * Allocates respectives textures to velocimeter and pointer.
 *
 * \param fMaximumSpeed Maximum speed the car can achieve.
 */
CarDisplay::CarDisplay(double fMaximumSpeed) : m_fMaximumSpeedSquared(fMaximumSpeed*fMaximumSpeed)
{
	// Gets texture manager instance.
	TextureManager* textureManager = TextureManager::getInstance();

	// Assigns and scale textures.
	m_velocimeter.setTexture(*textureManager->getTexturePointer("velocimeter"));
	m_velocimeter.scale(100.f / m_velocimeter.getTexture()->getSize().x, 100.f / m_velocimeter.getTexture()->getSize().y);

	m_velocimeterPointer.setTexture(*textureManager->getTexturePointer("pointer"));
	m_velocimeterPointer.setOrigin(m_velocimeterPointer.getTexture()->getSize().x / 2, m_velocimeterPointer.getTexture()->getSize().y / 2);
	m_velocimeterPointer.scale(100.f / m_velocimeterPointer.getTexture()->getSize().x, 100.f / m_velocimeterPointer.getTexture()->getSize().y);
	m_velocimeterPointer.setPosition(50, 50);
}

/*!
 * Uses maximum and current speed to find the right orientation for the velocimeter's pointer.
 *
 * \param fSpeedSquared Car's current velocity (squared).
 */
void CarDisplay::update(double fSpeedSquared)
{
	// Calculates the orientation for given speed.
	double orientation = fSpeedSquared * MAXIMUM_ROTATION / m_fMaximumSpeedSquared;
	// Updates pointer orientation.
	m_velocimeterPointer.setRotation(orientation);
}


void CarDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Draw sprites.
	target.draw(m_velocimeter);
	target.draw(m_velocimeterPointer);
}



CarDisplay::~CarDisplay()
{
}

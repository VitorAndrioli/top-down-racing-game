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
	m_speedometer.setTexture(*textureManager->getTexturePointer("speedometer"));
	m_speedometer.scale(60.f / m_speedometer.getTexture()->getSize().x, 60.f / m_speedometer.getTexture()->getSize().y);

	m_speedometerPointer.setTexture(*textureManager->getTexturePointer("pointer"));
	m_speedometerPointer.setOrigin(m_speedometerPointer.getTexture()->getSize().x / 2, m_speedometerPointer.getTexture()->getSize().y / 2);
	m_speedometerPointer.scale(60.f / m_speedometerPointer.getTexture()->getSize().x, 60.f / m_speedometerPointer.getTexture()->getSize().y);
	m_speedometerPointer.setPosition(30, 30);
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
	m_speedometerPointer.setRotation(orientation);
}


void CarDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Draw sprites.
	target.draw(m_speedometer);
	target.draw(m_speedometerPointer);
}



CarDisplay::~CarDisplay()
{
}

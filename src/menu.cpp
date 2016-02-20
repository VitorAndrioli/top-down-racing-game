#include "menu.h"


Menu::Menu(Vector2u windowSize)
{

}

Menu::Menu()
{
	m_bShowInitialMenu = true;
	m_bMultiPlayer = false;

	m_font.loadFromFile(".\\assets\\font\\Quartzo.ttf");

	// Read menu text
	std::ifstream instructionsFile(".\\assets\\txt\\menu.txt");
	std::string instructionsString((std::istreambuf_iterator<char>(instructionsFile)), std::istreambuf_iterator<char>());
	m_instructions.setFont(m_font);
	m_instructions.setCharacterSize(28);
	m_instructions.setString(instructionsString);
	m_instructions.setOrigin(m_instructions.getLocalBounds().width / 2, m_instructions.getLocalBounds().height / 2);

	TextureManager *textureManager = TextureManager::getInstance();

	m_initialMenuBackground.setTexture(*textureManager->getTexturePointer("menu_background"));
	m_initialMenuBackground.setOrigin(m_initialMenuBackground.getTexture()->getSize().x / 2, m_initialMenuBackground.getTexture()->getSize().y / 2); // Sets sprite's center as its origin (instead of its corner).
	
	m_pausedBackground.setSize(Vector2f(m_instructions.getLocalBounds().width + 15, m_instructions.getLocalBounds().height + 25));
	m_pausedBackground.setFillColor(Color(0, 0, 0, 120));
	m_pausedBackground.setOrigin(m_pausedBackground.getSize().x / 2, m_pausedBackground.getSize().y / 2);
		
	m_initialMenuSprite.setTexture(*textureManager->getTexturePointer("menu"));
	m_initialMenuSprite.setOrigin(m_initialMenuSprite.getTexture()->getSize().x / 2, m_initialMenuSprite.getTexture()->getSize().y / 4); // Sets sprite's center as its origin (instead of its corner).
	m_initialMenuSprite.scale(100.f / m_initialMenuSprite.getTexture()->getSize().x, 200.f / m_initialMenuSprite.getTexture()->getSize().y); // Scales texture to make sure it fits the car.
	
	m_arrowSprite.setTexture(*textureManager->getTexturePointer("arrow"));
	m_arrowSprite.setOrigin(m_arrowSprite.getTexture()->getSize().x / 2, m_arrowSprite.getTexture()->getSize().y / 4); // Sets sprite's center as its origin (instead of its corner).
	m_arrowSprite.scale(15.f / m_arrowSprite.getTexture()->getSize().x, 10.f / m_arrowSprite.getTexture()->getSize().y); // Scales texture to make sure it fits the car.


	
}

void Menu::toggleOptions()
{
	m_bMultiPlayer = !m_bMultiPlayer;

	if (m_bMultiPlayer)
	{
		m_arrowSprite.move(Vector2f(0, 40));
	}
	else
	{
		m_arrowSprite.move(Vector2f(0, -40));
	}
}

bool Menu::getOption()
{
	return m_bMultiPlayer;
}

void Menu::draw(RenderTarget &target, RenderStates states) const
{
	if (m_bShowInitialMenu)
	{
		target.draw(m_initialMenuBackground);
		target.draw(m_initialMenuSprite);
		target.draw(m_arrowSprite);
		//target.draw(m_instructions);
	}
	else
	{
		target.draw(m_pausedBackground);
		target.draw(m_instructions);
	}
	
}

void Menu::setSize(double x, double y)
{
	m_instructions.move(x / 2, y / 2);
	m_initialMenuSprite.move(x / 2, y / 2);
	m_pausedBackground.move(x / 2, y / 2);
	
	m_arrowSprite.move((x / 2) - 60, (y / 2) - 20);

	m_initialMenuBackground.scale(x / m_initialMenuBackground.getTexture()->getSize().x, y / m_initialMenuBackground.getTexture()->getSize().y); // Scales texture to make sure it fits the car.
	m_initialMenuBackground.move(x / 2, y / 2);
	
}


Menu::~Menu()
{
}

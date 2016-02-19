#include "menu.h"


Menu::Menu()
{

}

Menu::Menu(Vector2u windowSize)
{
	m_font.loadFromFile(".\\assets\\font\\Quartzo.ttf");

	// Read menu text
	std::ifstream instructionsFile(".\\assets\\txt\\menu.txt");
	std::string instructionsString((std::istreambuf_iterator<char>(instructionsFile)), std::istreambuf_iterator<char>());
	m_instructions.setFont(m_font);
	m_instructions.setCharacterSize(28);
	m_instructions.setString(instructionsString);
	m_instructions.setOrigin(m_instructions.getLocalBounds().width / 2, m_instructions.getLocalBounds().height / 2);
	m_instructions.move(windowSize.x / 2, windowSize.y / 2);


	FloatRect menuBackgroundRect = sf::FloatRect(0, 0, m_instructions.getLocalBounds().width + 15, m_instructions.getLocalBounds().height + 25);
	m_menuBackground.setSize(sf::Vector2f(menuBackgroundRect.width, menuBackgroundRect.height));
	m_menuBackground.setFillColor(sf::Color(0, 0, 0, 120));
	m_menuBackground.setOrigin(m_menuBackground.getSize().x / 2, m_menuBackground.getSize().y / 2);
	m_menuBackground.move(windowSize.x / 2, windowSize.y / 2);

	m_bShowInstructions = false;
}

void processKeyPress(sf::Keyboard::Key code)
{

}

void Menu::draw(RenderTarget &target, RenderStates states) const
{
	if (m_bShowInstructions)
	{
		target.draw(m_menuBackground);
		target.draw(m_instructions);
	}
	
}


Menu::~Menu()
{
}

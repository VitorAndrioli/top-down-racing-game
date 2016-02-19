#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>

using namespace sf;

class Menu : public Drawable
{
public:
	Menu();
	Menu(Vector2u windowSize);
	~Menu();
	void processKeyPress(Keyboard::Key code); //!< Action any key presses
	void draw(RenderTarget &target, RenderStates states) const; //!< Draw function (from sf::Drawable)

	Text m_instructions;
	RectangleShape m_menuBackground;
	Font m_font;
	bool m_bShowInstructions;
};


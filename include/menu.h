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
	void draw(RenderTarget &target, RenderStates states) const; //!< Draw function (from sf::Drawable)
	void setSize(double x, double y);
	void toggleOptions();
	bool getOption();

	RectangleShape m_pausedBackground;
	Text m_instructions;
	
	Texture m_initialMenuBackgroundTexture;
	Sprite m_initialMenuBackground;
	
	Texture m_initialMenuTexture; 
	Sprite m_initialMenuSprite;

	Texture m_arrowTexture;
	Sprite m_arrowSprite;

	Font m_font;
	bool m_bShowInitialMenu;
	bool m_bMultiPlayer;
};


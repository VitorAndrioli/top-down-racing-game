#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>

#include "textureManager.h"

using namespace sf;

class Menu : public Drawable
{
public:
	Menu();
	Menu(Vector2f windowSize);
	~Menu();
	void setSize(double x, double y);
	void toggleOptions();
	bool getOption();

	Sprite m_initialMenuBackground;
	Sprite m_initialMenuSprite;
	Sprite m_arrowSprite;

	bool m_bShowInitialMenu;
	bool m_bMultiPlayer;

private:
	void draw(RenderTarget &target, RenderStates states) const; //!< Draw function (from sf::Drawable)

};


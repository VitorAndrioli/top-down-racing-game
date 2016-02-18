/**
\file main.cpp
*/

/*! \mainpage Course Work - IMAT2605
* \brief Brief explanation
* More details explanation
*/


#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>
#include <array>

#include <string>
#include <fstream>
#include <streambuf>


using namespace sf;
int main()
{

	RenderWindow window(VideoMode(700, 600), "IMAT2605 Course work");
	window.setVerticalSyncEnabled(true);

	// Fonts used to write data to the screen.
	sf::Font font;
	font.loadFromFile(".\\assets\\font\\Quartzo.ttf");


	// Loading page.
	sf::Text loadingText("Loading...", font, 28);
	loadingText.setOrigin(loadingText.getLocalBounds().width / 2, loadingText.getLocalBounds().height / 2);
	loadingText.move(window.getSize().x / 2, window.getSize().y / 2);
	window.draw(loadingText);
	window.display();

	// Instantiats game.
	Game game;
	game.update(0);

	// Creates the instrunctions page.
	sf::View menuView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	menuView.setViewport(sf::FloatRect(0, 0, 1, 1));
	window.setView(menuView);
	window.clear(Color(0, 0, 0, 100));
	sf::Text menuText("", font, 28);

	// Read menu text
	string file1 = ".\\assets\\txt\\menu.txt";
	std::ifstream t(file1);
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	menuText.setString(str);
	menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height / 2);
	menuText.move(window.getSize().x / 2, window.getSize().y / 2);

	window.draw(menuText);
	window.display();

	
	
	sf::View mainView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	mainView.setViewport(sf::FloatRect(0, 0, 1, 1));

	sf::View miniView(sf::FloatRect(0, 0, 1500, 1600));
	miniView.setViewport(sf::FloatRect(0.8, 0, 0.2, 0.2));
	
	Clock clock;
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
				game.processKeyPress(event.key.code);
			if (event.type == Event::KeyReleased)
				game.processKeyRelease(event.key.code);
										
		}

		if (clock.getElapsedTime().asSeconds() > 0.0005)
		{
			if (!game.m_bPaused) game.update(clock.getElapsedTime().asSeconds());
			clock.restart();
		}

		window.setView(mainView);

		window.clear(Color::Magenta);

		window.draw(game);
		if (game.m_bPaused) window.draw(menuText);
			

		//mainView.setCenter(game.car.getPosition().getX(), game.car.getPosition().getY());

		//window.setView(miniView);
		//window.draw(game);
		
		

		window.display();
		

		
	}

	return 0;
}
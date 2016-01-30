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

using namespace sf;
int main()
{

	RenderWindow window(VideoMode(700, 600), "IMAT2605 Course work");
	
	Game game;

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
			game.update(clock.getElapsedTime().asSeconds());
			clock.restart();
		}

		window.clear(Color::Black);
		
		window.draw(game);
		
		window.display();
	}

	return 0;
}
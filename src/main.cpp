/**
\file main.cpp
*/

#include <SFML/Graphics.hpp>
#include "game.h"
#include "menu.h"
#include <iostream>
#include <array>

#include <string>
#include <fstream>
#include <streambuf>


using namespace sf;
int main()
{

	RenderWindow window(VideoMode(700, 700), "IMAT2605 Course work");
	window.setVerticalSyncEnabled(true);

	Game game;
	game.setMenuSize(window.getSize().x, window.getSize().y);
	
	sf::View menuView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	menuView.setViewport(sf::FloatRect(0, 0, 1, 1));

	sf::View player1View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	sf::View player2View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	
	do
	{
		window.clear(Color::Magenta);
		window.setView(menuView);
		window.draw(game);
		window.display();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				return 0;
			}
			if (event.type == Event::KeyPressed)
				game.processKeyPress(event.key.code);
		}

	} while (!game.hasStarted());

	game.load();
	if (game.isMultiplayer())
	{
		player2View.setViewport(sf::FloatRect(0, 0, 0.5, 1));
		player2View.setSize(window.getSize().x / 2, window.getSize().y);

		player1View.setViewport(sf::FloatRect(0.5, 0, 0.5, 1));
		player1View.setSize(window.getSize().x / 2, window.getSize().y);
	}
	else
	{
		player1View.setViewport(sf::FloatRect(0, 0, 1, 1));
		player1View.setSize(window.getSize().x, window.getSize().y);
	}


	sf::View miniView(sf::FloatRect(0, 0, 1500, 1600));
	miniView.setViewport(sf::FloatRect(0.8, 0, 0.2, 0.2));
	
	CarDisplay display;
	sf::View displayView(sf::FloatRect(0, 0, 100, 100));
	displayView.setViewport(sf::FloatRect(0, 0, 1, 1));

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


		window.clear(Color::Magenta);

		
		window.setView(player1View);
		player1View.setCenter(game.getP1Position());
		//player1View.setRotation(game.player1.getOrientation() * TO_DEGREES + 90);
		window.draw(game);

		if (game.isMultiplayer())
		{
			window.setView(player2View);
			player2View.setCenter(game.getP2Position());
			window.draw(game);
		}

		window.setView(miniView);
		window.draw(game);

		//window.setView(displayView);
		//window.draw(display);
		
		if (game.isPaused())
		{
			window.setView(menuView);
			window.draw(game.getInstructionsBackground());
			window.draw(game.getInstructions());
		}

		window.display();
	}

	return 0;
}
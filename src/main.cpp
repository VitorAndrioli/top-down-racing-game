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

	RenderWindow window(VideoMode(1200, 700), "IMAT2605 Course work");
	window.setVerticalSyncEnabled(true);

	Game game;
	game.setMenuSize(window.getSize().x, window.getSize().y);
	
	sf::View menuView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	menuView.setViewport(sf::FloatRect(0, 0, 1, 1));
	sf::View player1View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	sf::View player2View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

	sf::View mapView(sf::FloatRect(0, 0, 6700, 6700));
	mapView.setViewport(sf::FloatRect(0.8, 0, 0.2, 0.2));

	sf::View p1displayView(sf::FloatRect(0, 0, 60, 60));
	
	sf::View p2displayView(sf::FloatRect(0, 0, 60, 60));
	
	
	do
	{
		window.clear(Color(43, 130, 62, 255));
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
		player2View.setViewport(sf::FloatRect(0, 0, 0.499, 1));
		player2View.setSize(window.getSize().x / 2, window.getSize().y);
		p2displayView.setViewport(sf::FloatRect(0.02, 0.8, 0.17, 0.17));

		player1View.setViewport(sf::FloatRect(0.501, 0, 0.499, 1));
		player1View.setSize(window.getSize().x / 2, window.getSize().y);
		p1displayView.setViewport(sf::FloatRect(0.52, 0.8, 0.17, 0.17));

	}
	else
	{
		player1View.setViewport(sf::FloatRect(0, 0, 1, 1));
		player1View.setSize(window.getSize().x, window.getSize().y);
		p1displayView.setViewport(sf::FloatRect(0.02, 0.8, 0.17, 0.17));
	}

	Clock clock;
	player1View.setCenter(game.getP1Position());


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

		if (clock.getElapsedTime().asSeconds() > 0.001)
		{
			game.update(clock.getElapsedTime().asSeconds());
			clock.restart();
		}

		window.clear(Color::Yellow);

		
		window.setView(player1View);
		window.draw(game);
		//player1View.setCenter(game.getP1Position());
		//player1View.setRotation(game.player1.getOrientation() * TO_DEGREES + 90);
		
		window.setView(p1displayView);
		window.draw(*game.getP1Display());
		
		if (game.isMultiplayer())
		{
			window.setView(player2View);
			player2View.setCenter(game.getP2Position());
			window.draw(game);

			window.setView(p2displayView);
			window.draw(*game.getP2Display());

		}

		window.setView(mapView);
		window.draw(game);

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
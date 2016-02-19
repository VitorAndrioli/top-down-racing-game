//! \file game.cpp Implementation of Game class.


/*! \mainpage My Personal Index Page
*
* \section intro_sec Introduction
*
* This is the introduction.
*
* \section install_sec Installation
*
* \subsection step1 Step 1: Opening the box
*
* etc...
*/
#include "game.h"


using namespace std;

Game::Game()
{
	m_bPaused = true;
	m_bMultiPlayer = false;

	m_textureManager.loadTextures();

	m_background.setTexture(m_textureManager.m_aTexture.at(7));
	
	rapidxml::xml_document<> doc;
	ifstream file(".\\assets\\xml\\obstacles.xml");
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	string content(buffer.str());
	doc.parse<0>(&content[0]);
	rapidxml::xml_node<>* pRoot = doc.first_node();
	for (rapidxml::xml_node<> *pNode = pRoot->first_node("collidable"); pNode; pNode = pNode->next_sibling())
	{
		Collidable * newObstacle = CollidableFactory::NewCollidable(pNode, &m_textureManager);
		if (newObstacle != NULL)
		{
			obstacles.push_back(newObstacle);
			//obstacles.back()->setTexture(&m_textureManager.m_aTexture.at(1));
		}
		//*/
	}

	m_startGame = false;
}

void Game::setMode(bool mode)
{
	m_bMultiPlayer = m_menu.m_bMultiPlayer;
	
	player1 = Car(50, 350, -90 * TO_RADIANS);
	player1.setTexture(&m_textureManager.m_aTexture.at(1));
	player1.setWheelTexture(&m_textureManager.m_aTexture.at(4));

	if (m_bMultiPlayer)
	{
		player2 = Car(150, 350, -90 * TO_RADIANS);
		player2.setTexture(&m_textureManager.m_aTexture.at(2));
		player2.setWheelTexture(&m_textureManager.m_aTexture.at(4));
	}

	m_startGame = true;
	m_menu.m_bShowInitialMenu = false;
	m_bPaused = false;
}

void Game::setMenuSize(double x, double y)
{
	m_menu.setSize(x, y);
}

void Game::draw(RenderTarget &target, RenderStates states) const
{
	
	target.draw(m_background);
	target.draw(player1);
	if (m_bMultiPlayer) target.draw(player2);
	for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		target.draw(**it);
	}
}

void Game::update(float timestep)
{
	
	if (m_bPaused) return;
	player1.update(timestep);
	player2.update(timestep);
	//player1.print();
	
	if (m_bMultiPlayer && player1.isMoving()) player1.checkCollision(&player2);
	if (m_bMultiPlayer && player2.isMoving()) player2.checkCollision(&player1);

	for (auto it = obstacles.begin(); it != obstacles.end(); ++it) (*it)->update(timestep);
	
	for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		if (player1.isMoving()) player1.checkCollision(*it);
		if (m_bMultiPlayer && player2.isMoving()) player2.checkCollision(*it);
		
		if ((*it)->isMoving() || (*it)->isRotating()) (*it)->checkCollision(&player1);
		if (m_bMultiPlayer && ((*it)->isMoving() || (*it)->isRotating())) (*it)->checkCollision(&player2);
		
		for (auto it2 = obstacles.begin(); it2 != obstacles.end(); ++it2)
		{
			if (it2 != it)
			{
				if ((*it)->isMoving() || (*it)->isRotating())
				{
					(*it)->checkCollision(*it2);
				}
				
			}
		}
	}


}

void Game::processKeyPress(Keyboard::Key code)
{
	if (code == sf::Keyboard::Up)
	{
		if (m_bPaused) m_menu.toggleOptions();
		else player1.m_bAccelerating = true;
	}
	if (code == sf::Keyboard::Down) 
	{
		if (m_bPaused) m_menu.toggleOptions();
		else player1.m_bReversing = true;
	}

	if (code == sf::Keyboard::Right) player1.m_bTurningRight = true;
	if (code == sf::Keyboard::Left) player1.m_bTurningLeft = true;
	if (code == sf::Keyboard::RControl) player1.m_bBraking = true;
	
	if (code == sf::Keyboard::W) player2.m_bAccelerating = true;
	if (code == sf::Keyboard::S) player2.m_bReversing = true;
	if (code == sf::Keyboard::D)  player2.m_bTurningRight = true;
	if (code == sf::Keyboard::A)  player2.m_bTurningLeft = true;
	if (code == sf::Keyboard::LControl) player2.m_bBraking = true;

	if (code == sf::Keyboard::P) m_bPaused = !m_bPaused;
	if (code == sf::Keyboard::Return) if (!m_startGame) setMode(m_menu.getOption());
	

	if (code == sf::Keyboard::Space) obstacles.front()->m_fAngularVelocity = -5;

}

void Game::processKeyRelease(Keyboard::Key code)
{
	if (code == sf::Keyboard::Up) player1.m_bAccelerating = false;
	if (code == sf::Keyboard::Down) player1.m_bReversing = false;
	if (code == sf::Keyboard::Right)  player1.m_bTurningRight = false;
	if (code == sf::Keyboard::Left)  player1.m_bTurningLeft = false;
	if (code == sf::Keyboard::RControl) player1.m_bBraking = false;

	if (code == sf::Keyboard::W) player2.m_bAccelerating = false;
	if (code == sf::Keyboard::S) player2.m_bReversing = false;
	if (code == sf::Keyboard::D)  player2.m_bTurningRight = false;
	if (code == sf::Keyboard::A)  player2.m_bTurningLeft = false;
	if (code == sf::Keyboard::LControl) player2.m_bBraking = false;
}

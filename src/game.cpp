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


Game::Game() :
	m_bMultiPlayer(false),
	m_bPaused(true),
	m_pTextureManager(TextureManager::getInstance())
{ }

void Game::load()
{
	player1 = new Car(50, 350, -90 * TO_RADIANS);
	player1->setTexture(m_pTextureManager->getTexturePointer("car_01"));
	player1->setWheelTexture(m_pTextureManager->getTexturePointer("car_tyre"));
	
	if (m_bMultiPlayer)
	{
		player2 = new Car(150, 350, -90 * TO_RADIANS);
		player2->setTexture(m_pTextureManager->getTexturePointer("car_02"));
		player2->setWheelTexture(m_pTextureManager->getTexturePointer("car_tyre"));
	}

	CollidableFactory collidableFactory;
	m_background.setTexture(*m_pTextureManager->getTexturePointer("track"));

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
		//std::shared_ptr<Collidable> newObstacle = collidableFactory.makeCollidable(pNode);
		Collidable* newObstacle = collidableFactory.makeCollidable(pNode);
		if (newObstacle != NULL)
		{
			//obstacles.push_back(newObstacle);
			pObstacles.push_back(newObstacle);
		}
	}
}

void Game::setMode(bool mode)
{
	m_bMultiPlayer = m_menu.m_bMultiPlayer;
	
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
	target.draw(*player1);
	if (m_bMultiPlayer) target.draw(*player2);
	for (auto it = pObstacles.begin(); it != pObstacles.end(); ++it)
	{
		target.draw(**it);
	}
}

void Game::update(float timestep)
{
	
	if (m_bPaused) return;
	player1->update(timestep);
	if (m_bMultiPlayer) player2->update(timestep);
	//player1->print();
	
	if (m_bMultiPlayer && player1->isMoving()) player1->checkCollision(player2);
	if (m_bMultiPlayer && player2->isMoving()) player2->checkCollision(player1);

	for (auto it = pObstacles.begin(); it != pObstacles.end(); ++it)
	{
		(*it)->update(timestep);
		if (player1->isMoving() || player1->isRotating()) player1->checkCollision(*it);
		if (m_bMultiPlayer && (player2->isMoving() || player1->isRotating())) player2->checkCollision(*it);
		
		if ((*it)->isMoving() || (*it)->isRotating()) player1->checkCollision(*it);
		if (m_bMultiPlayer && ((*it)->isMoving() || (*it)->isRotating())) player2->checkCollision(*it);
		
		for (auto it2 = pObstacles.begin(); it2 != pObstacles.end(); ++it2)
		{
			if (it2 != it && ((*it)->isMoving() || (*it)->isRotating()))
			{
				(*it)->checkCollision(*it2);
			}
		}
	}


}

void Game::processKeyPress(Keyboard::Key code)
{
	if (code == Keyboard::Up)
	{
		if (m_bPaused) m_menu.toggleOptions();
		else player1->m_bAccelerating = true;
	}
	if (code == Keyboard::Down) 
	{
		if (m_bPaused) m_menu.toggleOptions();
		else player1->m_bReversing = true;
	}

	if (code == Keyboard::Right) player1->m_bTurningRight = true;
	if (code == Keyboard::Left) player1->m_bTurningLeft = true;
	if (code == Keyboard::RControl) player1->m_bBraking = true;
	
	if (code == Keyboard::W) player2->m_bAccelerating = true;
	if (code == Keyboard::S) player2->m_bReversing = true;
	if (code == Keyboard::D)  player2->m_bTurningRight = true;
	if (code == Keyboard::A)  player2->m_bTurningLeft = true;
	if (code == Keyboard::LControl) player2->m_bBraking = true;

	if (code == Keyboard::P) m_bPaused = !m_bPaused;
	if (code == Keyboard::Return) if (!m_startGame) setMode(m_menu.getOption());
	

	if (code == Keyboard::Space) pObstacles.front()->m_fAngularVelocity = -5;

}

void Game::processKeyRelease(Keyboard::Key code)
{
	if (code == Keyboard::Up) player1->m_bAccelerating = false;
	if (code == Keyboard::Down) player1->m_bReversing = false;
	if (code == Keyboard::Right)  player1->m_bTurningRight = false;
	if (code == Keyboard::Left)  player1->m_bTurningLeft = false;
	if (code == Keyboard::RControl) player1->m_bBraking = false;

	if (code == Keyboard::W) player2->m_bAccelerating = false;
	if (code == Keyboard::S) player2->m_bReversing = false;
	if (code == Keyboard::D)  player2->m_bTurningRight = false;
	if (code == Keyboard::A)  player2->m_bTurningLeft = false;
	if (code == Keyboard::LControl) player2->m_bBraking = false;
}

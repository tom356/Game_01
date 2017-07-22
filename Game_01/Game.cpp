#include "Game.h"
using namespace gamenamespace;

Player::Player() : GamePhysics::Object() {}
Player::Player(int x, int y, int w, int h) : GamePhysics::Object(x, y, w, h) {}
void Player::jump() 
{ 
	if(!jumping)
		force.y = -40;
	jumping = true;
}
void Player::playerOnGround() { jumping = false; }
void Player::moveLeft() { moveBy(-10, 0); }
void Player::moveRight() { moveBy(10, 0); }


Game::Game()
{
	sdlControl = SDLCtrl::getInstace();
	inputManager = InpManager::getInstace(sdlControl);
	gameTimer.setTick(17);//~60fps

	GamePhysics::gravity = 3;
	player.setPos(0, 0);
	player.setSize(100, 100);
	floor.setPos(0, 740);
	floor.setSize(1000, 100);
	GamePhysics::Object o(300, 700, 100, 100);	
	crates.push_back(o);
	o.setPos(400, 600);
	crates.push_back(o);
	o.setPos(500, 500);
	crates.push_back(o);
	o.setPos(600, 400);
	crates.push_back(o);
	o.setPos(300, 200);
	crates.push_back(o);
	o.setPos(200, 100);
	crates.push_back(o);

	sdlControl->init();
	mainLoop();
	sdlControl->clear();
}
Game::~Game()
{

}
void Game::processInput()
{
	inputManager->poll();

	gameOver = inputManager->getKeyboard().esc;	

	if (inputManager->getKeyboard().space)
		player.jump();
	if (inputManager->getKeyboard().left)
		player.moveLeft();
	if (inputManager->getKeyboard().right)
		player.moveRight();
	/*
	if (inputManager->getKeyboard().left)
		GamePhysics::applyForce(player, -5, 0);
	if (inputManager->getKeyboard().right)
		GamePhysics::applyForce(player, 5, 0);
	if(!inputManager->getKeyboard().left && !inputManager->getKeyboard().right)
		GamePhysics::applyForce(player, -player.getForce().x, 0);
		*/
}
bool Game::collisionDetection()
{
	if (GamePhysics::detectCollisionMoveing(player, floor))
	{
		GamePhysics::collideObjects(player, floor);
		return true;
	}
	for (int i = 0; i < crates.size(); i++)
	{
		if (GamePhysics::detectCollisionMoveing(player, crates[i]))
		{
			GamePhysics::collideObjects(player, crates[i]);
			return true;
		}
	}
	return false;
}
void Game::drawScene()
{
	sdlControl->drawImage("game_background.bmp", 0, 0, 1024, 762);
	sdlControl->drawImage("crate.bmp", player.getFrame().pos.x, player.getFrame().pos.y, player.getFrame().w, player.getFrame().h);
	for (int i = 0; i < crates.size(); i++)
		sdlControl->drawImage("crate.bmp", crates[i].getFrame().pos.x, crates[i].getFrame().pos.y, crates[i].getFrame().w, crates[i].getFrame().h);
	sdlControl->print();
}
void Game::mainLoop()
{	
	while(!gameOver)
	{		
		if (gameTimer.isTime())
		{
			processInput();

			GamePhysics::applyGravity(player);			
			if (collisionDetection())
				player.playerOnGround();
			else
				player.move();
			drawScene();
		}
	}
}
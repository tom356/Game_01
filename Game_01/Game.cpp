#include "Game.h"
using namespace gamenamespace;

Player::Player() : GamePhysics::Object() {}
Player::Player(int x, int y, int w, int h) : GamePhysics::Object(x, y, w, h) {}
void Player::jump() 
{ 
	if (jumping && force.y == 0)
		jumping = false;
	if (!jumping)
	{
		force.y = -40;
		jumping = true;
	}
}
void Player::playerOnGround() { jumping = false; }
void Player::moveLeft() 
{ 	
	force.x = -5;
}
void Player::moveRight()
{	
	force.x = 5;
}
void Player::stopped() 
{ 
	force.x = 0;
}

Game::Game()
{
	sdlControl = SDLCtrl::getInstace();
	inputManager = InpManager::getInstace(sdlControl);
	gameTimer.setTick(20);//~60fps
	renderTimer.setTick(20);
	GamePhysics::gravity = 3;
	player.setPos(0, 0);
	player.setSize(100, 100);
	floor.setPos(0, 710);
	floor.setSize(1000, 100);
	goal.setPos(700, 100);
	goal.setSize(100, 100);
	GamePhysics::Object o(480, 500, 100, 100);	
	crates.push_back(o);
	o.setPos(300, 400);
	crates.push_back(o);
	o.setPos(500, 200);
	crates.push_back(o);
	o.setPos(600, 100);
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
	if (!inputManager->getKeyboard().left && !inputManager->getKeyboard().right)
		player.stopped();
}
bool Game::collisionDetection()
{	
	GamePhysics::applyGravity(player);
	GamePhysics::collideObjects(player, floor);
	for (int i = 0; i < crates.size(); i++)
		GamePhysics::collideObjects(player, crates[i]);
	if (GamePhysics::collideObjects(player, goal))
		gameOver = true;
	return false;
}
void Game::drawScene()
{
	sdlControl->drawImage("game_background.bmp", 0, 0, 1024, 762);
	sdlControl->drawImage("crate.bmp", player.getFrame().pos.x, player.getFrame().pos.y, player.getFrame().w, player.getFrame().h);
	sdlControl->drawImage("crateFinish.bmp", goal.getFrame().pos.x, goal.getFrame().pos.y, goal.getFrame().w, goal.getFrame().h);
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
			collisionDetection();

			player.move();						
		}
		if (renderTimer.isTime())
		{
			drawScene();
			std::cout << player.getForce().x << ", " << player.getForce().y << std::endl;
		}
	}
}
#include "Game.h"
using namespace gamenamespace;

//------------Player-------------
Player::Player() : GamePhysics::Object(0,0,100,100) {}
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
//------------Level-------------
Level::Level()
{
	GamePhysics::Object o(0, 0, 0, 100);
	ledges.push_back(o);
}
Level::Level(int width, int height) 
{
	GamePhysics::Object o(0, height, width, 100);
	ledges.push_back(o);
}
Level::~Level() 
{
}
void Level::drawLevel(std::shared_ptr<SDLCtrl::SDLControl> s)
{
	s->drawImage("crateFinish.bmp", goal.getFrame().pos.x,
									goal.getFrame().pos.y,
									goal.getFrame().w,
									goal.getFrame().h);
	for (int i = 0; i < ledges.size(); i++)
		s->drawImage("ledge.bmp",	ledges[i].getFrame().pos.x,
									ledges[i].getFrame().pos.y,
									ledges[i].getFrame().w,
									ledges[i].getFrame().h);
}
void Level::setSize(int width, int height)
{
	ledges[0].getFrame().pos.x = 0;
	ledges[0].getFrame().pos.y = height;
	ledges[0].getFrame().w = width;
	ledges[0].getFrame().h = 100;
}
void Level::addLedge(int x, int y, int w, int h) 
{
	GamePhysics::Object o(x, y, w, h);
	ledges.push_back(o);
}
void Level::setGoalPos(int x, int y) 
{
	goal.setPos(x, y);
	goal.setSize(100, 100);
}
std::vector<GamePhysics::Object> &Level::getLedges() 
{
	return ledges;
}
GamePhysics::Object &Level::getGoal() 
{
	return goal;
}
//------------Game-------------
Game::Game()
{
	sdlControl = SDLCtrl::getInstace();
	inputManager = InpManager::getInstace(sdlControl);
	
	gameTimer.setTick(20);//~60fps
	renderTimer.setTick(20);//~60fps

	GamePhysics::gravity = 3;
		
	player.setSize(100, 100);
	
	currentLevel = -1;
	nextLevel();

	sdlControl->init();
	mainLoop();
	sdlControl->clear();
}
Game::~Game()
{

}
void Game::nextLevel()
{
	player.getFrame().pos.x = 0;
	player.getFrame().pos.y = SDLCtrl::HEIGHT - 110;
	if (++currentLevel < 4)
		makeLevel(currentLevel);
	else
		gameOver = true;
}
void Game::makeLevel(int level_id)
{
	Level l;
	switch (level_id)
	{
		case 0:
			l.setSize(SDLCtrl::WIDTH, SDLCtrl::HEIGHT);
			l.setGoalPos(200, SDLCtrl::HEIGHT-100);
			level = l;
		break;
		case 1:
			l.setSize(SDLCtrl::WIDTH, SDLCtrl::HEIGHT);
			l.setGoalPos(700, 100);
			l.addLedge(480, 540, 100, 50);
			l.addLedge(300, 440, 100, 50);
			l.addLedge(500, 240, 100, 50);
			l.addLedge(600, 140, 100, 50);
			level = l;
		break;
		case 2:
			l.setSize(SDLCtrl::WIDTH, SDLCtrl::HEIGHT);
			l.setGoalPos(900, 100);									
			l.addLedge(200, 540, 100, 50);
			l.addLedge(0, 440, 100, 50);
			l.addLedge(250, 240, 200, 50);
			l.addLedge(550, 240, 100, 50);
			level = l;
		break;
		case 3:
			l.setSize(SDLCtrl::WIDTH, SDLCtrl::HEIGHT);
			l.setGoalPos(900, SDLCtrl::HEIGHT-100);
			level = l;
			break;
		default:
		break;
	}	
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
	for (int i = 0; i < level.getLedges().size(); i++)
		GamePhysics::collideObjects(player, level.getLedges()[i]);
	if (GamePhysics::collideObjects(player, level.getGoal()))
		nextLevel();
	return false;
}
void Game::drawScene()
{
	sdlControl->drawImage("game_background.bmp", 0, 0, 1024, 762);
	sdlControl->drawImage("crate.bmp",	player.getFrame().pos.x, 
										player.getFrame().pos.y, 
										player.getFrame().w, 
										player.getFrame().h);
	level.drawLevel(sdlControl);
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
#include "Game.h"
using namespace GameMain;

//------------Game-------------
Game::Game()
{
	sdlControl = SDLCtrl::getInstace();
	inputManager = InpManager::getInstace(sdlControl);
	player = std::make_shared<Entities::Player>(0,0,100,100);

	gameTimer.setTick(20);//~60fps
	renderTimer.setTick(20);//~60fps
			
	levelMaker.init(sdlControl, player);

	currentLevel_id = -1;
	nextLevel();

	sdlControl->init();	
}
Game::~Game()
{

}
void Game::nextLevel()
{
	currentLevel.reset();	
	currentLevel = levelMaker.getLevel(++currentLevel_id);
	if( !currentLevel )	gameOver = true;
}
void Game::processInput()
{
	inputManager->poll(); // updates struct keyboard

	gameOver = inputManager->getKeyboard().esc;	// window close event is linked to esc as well

	if (inputManager->getKeyboard().space)
		player->jump();
	if (inputManager->getKeyboard().left)
		player->moveLeft();
	if (inputManager->getKeyboard().right)
		player->moveRight();
	if (!inputManager->getKeyboard().left && !inputManager->getKeyboard().right)
		player->stopped();
}
void Game::mainLoop()
{	
	while(!gameOver)
	{		
		if (gameTimer.isTime())
		{			
			processInput();						
			currentLevel->applyPhysics();				
		}
		
		if (renderTimer.isTime())
			currentLevel->drawLevel();

		if (currentLevel->isFinished())	
			nextLevel();
	}
}
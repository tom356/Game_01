#include "Game.h"
using namespace gamenamespace;

Game::Game()
{
	sdlControl = SDLCtrl::getInstace();
	inputManager = InpManager::getInstace(sdlControl);
	sdlControl->init();
	mainLoop();
	sdlControl->clear();
}
Game::~Game()
{

}
void Game::mainLoop()
{	
	
	GamePhysics::Object o(0, 0, 100, 100);
	GamePhysics::Vector v(5,0);
	GamePhysics::Vector stop(0, 0);
	GamePhysics::Vector jump(0, -3);
	//GamePhysics::gravity = 0.5;
	//GamePhysics::applyForce(o, v);
	while(!inputManager->getKeyboard().esc)
	{		
		inputManager->poll();
		if (o.getFrame().pos.y < 620)
			GamePhysics::applyGravity(o);
		else
			o.getForce() = stop;
		if(inputManager->getKeyboard().space)
			GamePhysics::applyForce(o, jump);
		if (inputManager->getKeyboard().left)
			o.getFrame().pos.x -= 5;
		if (inputManager->getKeyboard().right)
			o.getFrame().pos.x += 5;
		o.move();

		sdlControl->drawImage("game_background.bmp",0,0,1024,762);
		sdlControl->drawImage("crate.bmp", o.getFrame().pos.x, o.getFrame().pos.y,100,100);
		sdlControl->print();
	}
}
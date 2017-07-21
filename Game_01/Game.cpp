#include "Game.h"
using namespace gamenamespace;

Game::Game()
{
	sdlControl = SDLCtrl::getInstace();
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
	GamePhysics::gravity = 0.5;
	GamePhysics::applyForce(o, v);
	while(true)
	{
		if (o.getFrame().pos.y < 620)
		{
			GamePhysics::applyGravity(o);
			o.move();
		}

		if(sdlControl->getEvent().type == SDL_QUIT)break;
		sdlControl->drawImage("game_background.bmp",0,0,1024,762);
		sdlControl->drawImage("crate.bmp", o.getFrame().pos.x, o.getFrame().pos.y,100,100);
		sdlControl->print();
	}
}
#include"LevelControl.h"
//------------Level-------------
Level::Level()
{	
}
Level::Level(int playerX, int playerY, int goalX, int goalY, 
			SDLCtrl::SDLControlSP sdlControl, Entities::PlayerSP player)
{
	initLevel(playerX, playerY, goalX, goalY, sdlControl, player);
}
Level::~Level()
{
}
void Level::initLevel(int playerX, int playerY, int goalX, int goalY, 
			SDLCtrl::SDLControlSP sdlControl, Entities::PlayerSP player)
{
	this->sdlControl = sdlControl;
	this->player = player;

	player->setPos(playerX, playerY);

	goal.setPos(goalX, goalY);
	goal.setSize(100, 100);

	levelClear = false;
}
void Level::drawLevel()
{
	sdlControl->drawImage("game_background.bmp", 0, 0, 1024, 762);
	sdlControl->drawImage("crate.bmp",		player->getFrame().pos.x,
											player->getFrame().pos.y,
											player->getFrame().w,
											player->getFrame().h);	

	sdlControl->drawImage("crateFinish.bmp",goal.getFrame().pos.x,
											goal.getFrame().pos.y,
											goal.getFrame().w,
											goal.getFrame().h);
	for (int i = 0; i < ledges.size(); i++)
		sdlControl->drawImage("ledge.bmp",	ledges[i].getFrame().pos.x,
											ledges[i].getFrame().pos.y,
											ledges[i].getFrame().w,
											ledges[i].getFrame().h);
	sdlControl->print();
}
void Level::applyPhysics()
{
	// applies gravity, with object therminal velocity
	GamePhysics::applyGravity(*player.get());

	// checks for collision and if true, reduces force in the collision direction
	for (int i = 0; i < ledges.size(); i++)
		GamePhysics::collideObjects(*player.get(), ledges[i]);
	
	// littile bit messy passing it like that
	if(GamePhysics::collideObjects(*player.get(), goal))
		levelClear = true;

	// applies force to a player, not sure about function name
	player->move(); 	
}
void Level::addLedge(int x, int y, int w, int h)
{
	GamePhysics::Object o(x, y, w, h);
	ledges.push_back(o);
}
bool Level::isFinished() { return levelClear; }


//------------LevelMaker-------------
LevelMaker::LevelMaker() {}
LevelMaker::~LevelMaker() {}
void LevelMaker::init(	SDLCtrl::SDLControlSP sdlControl, Entities::PlayerSP player)
{
	this->sdlControl = sdlControl;
	this->player = player;
}

LevelSP LevelMaker::getLevel(int level_id)
{
	LevelSP l = NULL;
	switch (level_id)
	{
	case 0:
		l = std::make_shared<Level>();
		l->initLevel(0, SDLCtrl::HEIGHT - 100, 200, SDLCtrl::HEIGHT - 100, sdlControl, player);
		l->addLedge(0, SDLCtrl::HEIGHT, SDLCtrl::WIDTH, 100);
	break;
	case 1:
		l = std::make_shared<Level>();
		l->initLevel(0, SDLCtrl::HEIGHT - 100, 700, 100, sdlControl, player);
		l->addLedge(0, SDLCtrl::HEIGHT, SDLCtrl::WIDTH, 100);
		l->addLedge(480, 540, 100, 50);
		l->addLedge(300, 440, 100, 50);
		l->addLedge(500, 240, 100, 50);
		l->addLedge(600, 140, 100, 50);
	break;
	case 2:	
		l = std::make_shared<Level>();
		l->initLevel(0, SDLCtrl::HEIGHT - 100, 900, 100, sdlControl, player);		
		l->addLedge(0, SDLCtrl::HEIGHT, SDLCtrl::WIDTH, 100);
		l->addLedge(200, 540, 100, 50);
		l->addLedge(0, 440, 100, 50);
		l->addLedge(250, 240, 200, 50);
		l->addLedge(550, 240, 100, 50);
	break;
	case 3:
		l = std::make_shared<Level>();
		l->addLedge(0, SDLCtrl::HEIGHT, SDLCtrl::WIDTH, 100);
		l->initLevel(0, SDLCtrl::HEIGHT - 100, 900, SDLCtrl::HEIGHT - 100, sdlControl, player);
	break;
	default:
	break;
	}

	return l;
}
#pragma once
#include <memory>
#include <iostream>
#include "Physics.h"
#include "SDLController.h"
#include "Entities.h"

//namespace
class Level
{	
	SDLCtrl::SDLControlSP sdlControl;
	Entities::PlayerSP player;
	GamePhysics::Object goal;
	std::vector<GamePhysics::Object> ledges;	
	
	bool levelClear;

public:

	Level();
	Level(int playerX, int playerY, int goalX, int goalY, 
		SDLCtrl::SDLControlSP sdlControl, Entities::PlayerSP player);
	~Level();

	void initLevel(int playerX, int playerY, int goalX, int goalY, 
		SDLCtrl::SDLControlSP sdlControl, Entities::PlayerSP player);
	void addLedge(int x, int y, int w, int h);
	void drawLevel();
	void applyPhysics();
	bool isFinished();
};
using LevelSP = std::shared_ptr<Level>;

class LevelMaker
{
	SDLCtrl::SDLControlSP sdlControl;
	Entities::PlayerSP player;
public:
	LevelMaker();
	~LevelMaker();	
	void init(SDLCtrl::SDLControlSP sdlControl,	Entities::PlayerSP player);
	LevelSP getLevel(int level);
};
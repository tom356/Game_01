#pragma once
#include <memory>
#include <iostream>
#include "Physics.h"
#include "SDLController.h"
#include "Entities.h"
class Level
{	
	std::shared_ptr<SDLCtrl::SDLControl> sdlControl;
	std::shared_ptr<Entities::Player> player;
	GamePhysics::Object goal;
	std::vector<GamePhysics::Object> ledges;	
	
	bool levelClear;
public:
	Level();
	Level(int playerX, int playerY, int goalX, int goalY, 
			std::shared_ptr<SDLCtrl::SDLControl> sdlControl, std::shared_ptr<Entities::Player> player);
	~Level();
	void initLevel(int playerX, int playerY, int goalX, int goalY, 
			std::shared_ptr<SDLCtrl::SDLControl> sdlControl, std::shared_ptr<Entities::Player> player);
	void addLedge(int x, int y, int w, int h);
	void drawLevel();
	void applyPhysics();
	bool isFinished();
	//std::vector<GamePhysics::Object> &getLedges();
	//GamePhysics::Object &getGoal();
};
class LevelMaker
{
	std::shared_ptr<SDLCtrl::SDLControl> sdlControl;
	std::shared_ptr<Entities::Player> player;
public:
	LevelMaker();
	~LevelMaker();
	void init(	std::shared_ptr<SDLCtrl::SDLControl> sdlControl, 
				std::shared_ptr<Entities::Player> player);
	std::shared_ptr<Level> getLevel(int level);
};

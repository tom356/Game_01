#pragma once
#include <memory>
#include <iostream>
#include "SDLController.h"
#include "InputManager.h"
#include "Physics.h"
#include "Utils.h"
namespace gamenamespace
{		
	
	class Player : public GamePhysics::Object
	{
		bool jumping;
		bool moveing;
	public:
		Player();
		Player(int x, int y, int w, int h);
		void jump();
		void moveLeft(); 
		void moveRight();
		void stopped();
		void playerOnGround();
	};
		
	class Level
	{		
		std::vector<GamePhysics::Object> ledges;
		GamePhysics::Object goal;		
	public:
		Level();
		Level(int width, int height);
		~Level();
		void setSize(int width, int height);
		void addLedge(int x, int y, int w, int h);
		void setGoalPos(int x, int y);
		void drawLevel(std::shared_ptr<SDLCtrl::SDLControl> s);
		std::vector<GamePhysics::Object> &getLedges();
		GamePhysics::Object &getGoal();
	};
	class Game
	{
		gameUtility::Timer gameTimer;
		gameUtility::Timer renderTimer;
		Player player;		
		Level level;
		int currentLevel;

		GamePhysics::Vector JumpVector;
		std::shared_ptr<SDLCtrl::SDLControl> sdlControl;
		std::shared_ptr<InpManager::InputManager> inputManager;
		bool gameOver;

		void makeLevel(int level_id);
		void processInput();
		bool collisionDetection();
		void drawScene();
		void nextLevel();
	public:

		Game();
		~Game();		
		void mainLoop();		
	};
}
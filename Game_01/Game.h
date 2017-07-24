#pragma once
#include <memory>
#include <iostream>
#include "SDLController.h"
#include "InputManager.h"
#include "Physics.h"
#include "Utils.h"
#include "Entities.h"
#include "LevelControl.h"
/*
	Main Game file
	Controls the flow of the program
	all nececery subcomponents of allication meets here
*/
namespace GameMain
{		
	class Game
	{
		std::shared_ptr<SDLCtrl::SDLControl> sdlControl;
		std::shared_ptr<InpManager::InputManager> inputManager;
		std::shared_ptr<Entities::Player> player;
		std::shared_ptr<Level> currentLevel;
		gameUtility::Timer gameTimer;
		gameUtility::Timer renderTimer;
		LevelMaker levelMaker;

		int currentLevel_id;		
		bool gameOver;

		void processInput();
		void nextLevel();
	public:

		Game();
		~Game();		
		void mainLoop();		
	};
}
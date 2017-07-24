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
	Main Game
	Controls the flow of the program
	all nececery subcomponents of allication meets here
*/
namespace GameMain
{		
	class Game
	{
		SDLCtrl::SDLControlSP sdlControl;
		InpManager::InputManagerSP inputManager;
		Entities::PlayerSP player;
		LevelSP currentLevel;
		
		LevelMaker levelMaker;		
		gameUtility::Timer gameTimer;
		gameUtility::Timer renderTimer; // not used		
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
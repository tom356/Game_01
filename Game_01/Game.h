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
		
	class Game
	{
		gameUtility::Timer gameTimer;
		gameUtility::Timer renderTimer;
		Player player;

		GamePhysics::Object floor;
		std::vector<GamePhysics::Object> crates;
		GamePhysics::Object goal;

		GamePhysics::Vector JumpVector;
		std::shared_ptr<SDLCtrl::SDLControl> sdlControl;
		std::shared_ptr<InpManager::InputManager> inputManager;
		bool gameOver;
	public:

		Game();
		~Game();		
		void mainLoop();
		void processInput();
		bool collisionDetection();
		void drawScene();
	};
}
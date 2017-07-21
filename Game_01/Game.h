#pragma once
#include <memory>
#include "SDLController.h"
#include "InputManager.h"
#include "Physics.h"
namespace gamenamespace
{
	class Game
	{
		std::shared_ptr<SDLCtrl::SDLControl> sdlControl;
		std::shared_ptr<InpManager::InputManager> inputManager;

	public:

		Game();
		~Game();
		void mainLoop();
	};
}
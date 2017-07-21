#pragma once
#include <memory>
#include "SDLController.h"
#include "Physics.h"
namespace gamenamespace
{
	class Game
	{
		std::shared_ptr<SDLCtrl::SDLControl> sdlControl;

	public:

		Game();
		~Game();
		void mainLoop();
	};
}
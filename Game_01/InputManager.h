#pragma once
#include "SDLController.h"
namespace InpManager
{	
	struct Keyboard
	{
		bool left, right, esc, space;
		Keyboard();
	};
	struct Mouse
	{
		int x, y;
		bool lmb, rmb;
		Mouse();
	};
	class InputManager
	{
		Keyboard keyboard;
		Mouse mouse;
		SDL_Event event;
		std::shared_ptr<SDLCtrl::SDLControl> sdlControl;
	public:
		InputManager(std::shared_ptr<SDLCtrl::SDLControl> sdlControl);
		void poll();
		Keyboard &getKeyboard();
		Mouse &getMouse();
	};
	static std::shared_ptr<InputManager> getInstace(std::shared_ptr<SDLCtrl::SDLControl> sdlControl)
	{
		std::shared_ptr<InputManager> ptr = std::make_shared<InputManager>(sdlControl);
		return ptr;
	}
}
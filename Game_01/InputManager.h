#pragma once
#include "SDLController.h"
namespace InpManager
{	
	struct Keyboard
	{
		bool left, right, esc, space, l;
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
		SDLCtrl::SDLControlSP sdlControl;

		Keyboard keyboard;
		Mouse mouse;
		SDL_Event event;

	public:

		InputManager(SDLCtrl::SDLControlSP sdlControl);
		void poll();
		const Keyboard &getKeyboard();
		const Mouse &getMouse();
	};
	
	using InputManagerSP = std::shared_ptr<InputManager>;

	static InputManagerSP getInstace(SDLCtrl::SDLControlSP sdlControl)
	{
		auto ptr = std::make_shared<InputManager>(sdlControl);
		return ptr;
	}
}
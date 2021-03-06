#include "InputManager.h"
using namespace InpManager;

//------------Keyboard-------------
Keyboard::Keyboard()
{
	l = false;
	left = false;
	right = false;
	esc = false;
	space = false;
}

//------------Mouse-------------
Mouse::Mouse() 
{
	x = 0;
	y = 0;
	lmb = false;
	rmb = false;
}


//------------InputManager-------------
InputManager::InputManager(SDLCtrl::SDLControlSP sdlControl)
{
	this->sdlControl = sdlControl;
}
void InputManager::poll()
{
	if (sdlControl->getEvent(event))
	{
		switch (event.type)
		{
			case SDL_QUIT: keyboard.esc = true; break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_l: keyboard.l = true; break;
					case SDLK_LEFT: keyboard.left = true; break;
					case SDLK_RIGHT: keyboard.right = true; break;
					case SDLK_ESCAPE: keyboard.esc = true; break;
					case SDLK_SPACE: keyboard.space = true; break;
				}
			break;

			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
					case SDLK_l: keyboard.l = false; break;
					case SDLK_LEFT: keyboard.left = false; break;
					case SDLK_RIGHT: keyboard.right = false; break;
					case SDLK_ESCAPE: keyboard.esc = false; break;
					case SDLK_SPACE: keyboard.space = false; break;
				}
			break;
		}
	}
}
const Keyboard &InputManager::getKeyboard()
{
	return keyboard;
}
const Mouse &InputManager::getMouse()
{
	return mouse;
}
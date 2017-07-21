#include "SDLController.h"
using namespace SDLCtrl;

SDLControl::SDLControl()
{
	init();
}
SDLControl::~SDLControl()
{

}
bool SDLControl::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { return false; }

	window = SDLWrapper::createWindow("Game_01",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
		SDL_WINDOW_ALLOW_HIGHDPI /*|| SDL_WINDOW_MAXIMIZED*/);
	if (!window) return false;
	//SDL_SetWindowFullscreen(window.get(), SDL_WINDOW_FULLSCREEN);

	window_surface = SDLSurfaceUPtr(SDLWrapper::createWindowSurface(window.get()));
	if (!window_surface) return false;

	return true;
}
bool SDLControl::clear()
{
	//SDL_Quit();
	return true;
}
const SDL_Event& SDLControl::getEvent()
{
	SDL_PollEvent(&windowEvent);
	return windowEvent;
}
void SDLControl::drawImage(std::string fileName, int x, int y, int w, int h)
{
	if (images.find(fileName) == images.end())
		images[fileName] = SDLSurfaceUPtr(SDLWrapper::createImage(fileName.c_str()));
	if (images[fileName])
	{
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		SDL_BlitSurface(images[fileName].get(), NULL, window_surface.get(), &rect);
	}
}
void SDLControl::print()
{
	SDL_UpdateWindowSurface(window.get());
}


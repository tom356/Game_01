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
	
	window_surface = SDLSurfaceUPtr(SDLWrapper::createWindowSurface(window.get()));
	if (!window_surface) return false;

	return true;
}
int SDLControl::getEvent(SDL_Event& e)
{	
	return SDL_PollEvent(&e);
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
		source_rect.x = 0;
		source_rect.y = 0;
		source_rect.w = w;
		source_rect.h = h;		
		SDL_BlitSurface(images[fileName].get(), &source_rect, window_surface.get(), &rect);
	}
}
void SDLControl::print()
{
	SDL_UpdateWindowSurface(window.get());
}


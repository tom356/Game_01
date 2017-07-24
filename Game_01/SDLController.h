#pragma once
#include <String>
#include <Memory>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
namespace SDLCtrl
{	
	// not sure if this should not be a separate class
	namespace SDLWrapper
	{
		struct SDLDeleter
		{
			inline void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
			inline void operator()(SDL_Surface *p) const { SDL_FreeSurface(p); p = NULL; }

		};
		inline std::unique_ptr<SDL_Window, SDLDeleter>
			createWindow(char const *title, int x, int y, int w, int h, Uint32 flags)
		{
			return std::unique_ptr<SDL_Window, SDLDeleter>(
				SDL_CreateWindow(title, x, y, w, h, flags),
				SDLDeleter());
		}
		inline std::unique_ptr<SDL_Surface, SDLDeleter>
			createImage(char const *filename)
		{
			return std::unique_ptr<SDL_Surface, SDLDeleter>(
				SDL_LoadBMP(filename),
				SDLDeleter());
		}		
		inline std::unique_ptr<SDL_Surface, SDLDeleter>
			createWindowSurface(SDL_Window *window)
		{
			auto p = std::unique_ptr<SDL_Surface, SDLDeleter>(
				SDL_GetWindowSurface(window),
				SDLDeleter());
			return p;
		}
	}
	const int WIDTH = 1024, HEIGHT = 762;
	using SDLWindowUptr = std::unique_ptr<SDL_Window, SDLWrapper::SDLDeleter>;
	using SDLSurfaceUPtr = std::unique_ptr<SDL_Surface, SDLWrapper::SDLDeleter>;
	
	class SDLControl
	{
		SDLWindowUptr window;
		SDLSurfaceUPtr window_surface;
		std::map<std::string, SDLSurfaceUPtr> images;
		SDL_Rect rect;
		SDL_Rect source_rect;

	public:

		SDLControl();
		~SDLControl();
		bool init();
		int getEvent(SDL_Event& e);
		void drawImage(std::string fileName, int x, int y, int w, int h);
		void print();
	};
	static std::shared_ptr<SDLControl> getInstace() 
	{ 
		std::shared_ptr<SDLControl> ptr = std::make_shared<SDLControl>();
		return ptr;
	}
}
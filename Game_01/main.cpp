#include<iostream>
#include"Game.h"

void lunch()
{
	auto game = std::make_unique<gamenamespace::Game>();
	game->mainLoop();
}
int main(int argc, char*argv[])
{

	lunch();
	SDL_Quit();
	return EXIT_SUCCESS;
}
#include<iostream>
#include"Game.h"
/*
	Sample game, nothing to fancy.
	There are things to be done, some typenames and aliases for one.
	Also would be nice to name certain things a bit more obvious, not enaugh time though.
	Then there is the structure of program itself, not sure about certain solutions,
	Like, the way that the refrence is being passed from class Level.applyPhisics to gamePhysics functions
	But then again physics engine should be replaced anyway, i cannot compete with stuff like Box 2d, it still was fun working on it, has some potential
*/

// just to be sure that everything sdl get deleted before SDL_Quit, got some nasty bugs previously
// can be replaced with something like smart pointer that gets reset after loop or something
void lunch()
{
	GameMain::Game game;
	game.mainLoop();
}
int main(int argc, char*argv[])
{
	lunch();
	SDL_Quit();
	return EXIT_SUCCESS;
}
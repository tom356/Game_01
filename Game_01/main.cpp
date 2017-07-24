#include<iostream>
#include"Game.h"
/*
	Sample game,
	Things can be done better, like adding more typenames and aliases for certain things.
	Also would be nice to name things a bit more obvious and check what can be passed as reference and what needs to be a pointer.
	Then there is the structure of program itself, not sure about certain solutions,
	Physics engine is a bit plain and not very optimalized, guess i will switch to box 2d to see how it will run, it was fun working on it though
	I've used diffrent design approches for diffrent things, mainly to show diffrent styles of coding.
	Although i wasnt sure if presenting unified style code wouldn't be a better idea
*/

// just to be sure that everything sdl get deleted before SDL_Quit, got some nasty bugs previously
// lunch could be replaced with something like smart pointer that gets .reset() after game.mainLoop();
void lunchGame()
{
	GameMain::Game game;
	game.mainLoop();
}
int main(int argc, char*argv[])
{
	lunchGame();
	SDL_Quit();
	return EXIT_SUCCESS;
}
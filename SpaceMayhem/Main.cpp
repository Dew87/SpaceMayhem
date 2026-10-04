#include "Game.hpp"

int main(int argc, char *argv)
{
	Game::initialize("lua\\Game.lua");

	Game game;
	game.run();

	Game::finalize();

	return 0;
}

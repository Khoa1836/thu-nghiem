#include "Game.h"

int main()
{
	Game* game = new Game();
	game->run();
	delete game;

	return 0;
}
// cout << "HELLO CAC EM";
// cout << "hello world";
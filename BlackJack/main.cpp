#include "Game.h"

int main() 
{
	Game* game = new Game(true); // parameter: debug? currently not functional. change DebugDeck to Deck in Game.h, and this parameter to false, for normal play.

	return 0;
}
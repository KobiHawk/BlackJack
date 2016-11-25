#pragma once
#include "Deck.h"
#include "DebugDeck.h"
#include "Player.h"
#include "Dealer.h"
#include "Flags.h"

static const int MIN_BET = 5;
static const int MAX_BET = 500;


class Game
{
public:
	Game();
	~Game();

	void playRound();
	void splitGame(Player* thePlayer);
	void resetGame();
	void displayHelpMessage();
	void endGame(Player* thePlayer);
	bool checkBust(Player* thePlayer);

	
private:
#ifdef _BLACKJACK_DEBUG
	DebugDeck _deck;
#else 
	Deck _deck;
#endif
	Player _player;
	Dealer _dealer;
	int _bet;
};


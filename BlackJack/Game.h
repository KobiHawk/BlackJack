#pragma once
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"

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
	Deck _deck;
	Player _player;
	Dealer _dealer;
	int _bet;
	int _minBet;
	int _maxBet;
};


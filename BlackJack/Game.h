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
	void resetGame();
	void displayHelpMessage();
	void endGame();
	
private:
	Deck _deck;
	Player _player;
	Dealer _dealer;
	int _minBet;
	int _maxBet;
};


#pragma once
#include "Deck.h"
#include "Player.h"
class Game
{
public:
	Game();
	~Game();

	void playRound();
private:
	Deck _deck;
	Player _player;
	int _minBet;
	int _maxBet;
};


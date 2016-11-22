#pragma once
#include "Player.h"

class Dealer : public Player
{
public:
	Dealer();
	~Dealer();

	Card* getRevealedCard();
	void printHand();
};


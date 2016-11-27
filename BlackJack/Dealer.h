#pragma once
#include "Player.h"

/*
Dealer.h
Child of Player

The dealer only has one revealed card, and can only take very limited actions.
*/

class Dealer : public Player
{
public:
	Dealer();
	~Dealer();

	Card* getRevealedCard();
	void printHand();
};


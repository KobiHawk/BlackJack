#pragma once
#include "Player.h"

class Dealer : public Player
{
public:
	Dealer();
	~Dealer();

	Card* getRevealedCard() { return _revealedCard; }

private:
	Card* _revealedCard;
};


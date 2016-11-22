#pragma once
#include "Card.h"
class Player
{
public:
	Player();
	~Player();

	int getChips() { return _chips; }
	void drawCard(Card* card);

private:
	int _chips;
	int _totalCards;
	int _sum;
	bool _isAce;
	Card* _cards[11]; //11 is the maximum number of cards you can have before busting
};


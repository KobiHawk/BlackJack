#include "Dealer.h"
#include <iostream>

Dealer::Dealer() : Player()
{
}


Dealer::~Dealer()
{
}

Card* Dealer::getRevealedCard()
{
	if (_totalCards == 0)
	{
		return nullptr;
	}
	else
	{
		return _cards[0];
	}
}

void Dealer::printHand()
{
	std::cout << "Dealer cards: " << std::endl;
	for (int i = 0; i < _totalCards; i++)
	{
		_cards[i]->printCard();
	}
}
#include "Dealer.h"

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
#include "Player.h"



Player::Player() :
	_chips(0),
	_totalCards(0),
	_sum(0),
	_isAce(false)
{
}


Player::~Player()
{
}

void Player::drawCard(Card* card)
{
	_cards[_totalCards] = card;
	_totalCards++;
	_sum += card->getValue();

	if (card->getFace == 'A')
	{
		_isAce = true;
	}
}
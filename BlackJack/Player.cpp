#include "Player.h"



Player::Player() :
	_chips(100),
	_totalCards(0),
	_sum(0),
	_isAce(false)
{
}
Player::Player(int chips) :
	_chips(chips),
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

	//TODO
	/*
	if (card->getFace == 'A')
	{
		_isAce = true;
	}
	*/
}

void Player::printHand()
{
	for (int i = 0; i < _totalCards; i++)
	{
		_cards[i]->printCard();
	}
}
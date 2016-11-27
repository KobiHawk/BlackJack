#include "Player.h"
#include <iostream>


Player::Player() :
	_chips(100),
	_totalCards(0),
	_sum(0),
	_numAces(0),
	_hasBlackjack(false)
{
}
Player::Player(int chips) :
	_chips(chips),
	_totalCards(0),
	_sum(0),
	_numAces(0),
	_hasBlackjack(false)
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


	if (card->getFace() == 'A')
	{
		_numAces++;
	}
}

void Player::printHand()
{
	std::cout << "Player cards: " << std::endl;
	for (int i = 0; i < _totalCards; i++)
	{
		_cards[i]->printCard();
	}
}

//Splits can only be done on a paired hand
bool Player::checkSplit()
{
	bool result = false;

	if (_cards[0]->getValue() == _cards[1]->getValue())
	{
		if (_cards[0]->getFace() == _cards[1]->getFace())
		{
			result = true;
		}
	}

	return result;
}
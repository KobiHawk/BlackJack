#pragma once
#include "Card.h"
class Player
{
public:
	Player();
	Player(int chips);
	~Player();

	
	void drawCard(Card* card);
	void printHand();
	bool checkSplit();

	int getChips() { return _chips; }
	int getSum() { return _sum; }
	int getAces() { return _numAces; }
	int getCards() { return _totalCards; }
	Card* getSpecificCard(int index) { return _cards[index]; }
	bool getBlackjack() { return _hasBlackjack; }

	void changeAces(int change) { _numAces += change; }
	void changeSum(int change) { _sum += change; }
	void changeChips(int change) { _chips += change; }
	void setBlackjack(bool blackjack) { _hasBlackjack = blackjack; }

protected:
	int _chips;
	int _totalCards;
	int _sum;
	int _numAces;
	Card* _cards[11]; //11 is the maximum number of cards you can have before busting

	bool _hasBlackjack;
};


#pragma once

#include "Card.h"

static const int DECK_SIZE = 52;

class Deck
{
public:
	Deck();
	~Deck();

	void initDeck();
	void shuffle();
	Card* draw();
	void swap(int index1, int index2); // swaps two positions in the deck. used in shuffle.

protected:
	Card* _deck[DECK_SIZE];
	int _topOfDeck; //the index of the top card of the deck.
};


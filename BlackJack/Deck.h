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
	Card draw();
	void swap(int index1, int index2); // swaps two positions in the deck. used in shuffle.

private:
	Card* _deck[DECK_SIZE];
};


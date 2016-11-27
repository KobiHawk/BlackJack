#pragma once

#include "Card.h"

/*
Deck.h

The Deck class, which contains 52 normal playing cards.

Card* _deck[DECK_SIZE]: The deck is an array of Cards with length 52.
int _topOfDeck: This is the index of where the player currently is in the deck.
Whenever a card is drawn, this index is incremented.
*/

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


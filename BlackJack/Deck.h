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

private:
	Card* _deck;
};


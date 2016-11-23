#include "Deck.h"
#include <iostream>
#include <random>
#include <time.h>
Deck::Deck() :
	_topOfDeck(0)
{
	srand(time(NULL));
	initDeck();
	shuffle();
}


Deck::~Deck()
{
}

void Deck::shuffle()
{
	_topOfDeck = 0;
	for (int i = 0; i < 7; i++) // 7 iterations to increase variance
	{
		for (int j = 0; j < DECK_SIZE; j++)
		{
			swap(j, (rand() % DECK_SIZE));
		}
	}
}
Card* Deck::draw()
{
	if (_topOfDeck >= DECK_SIZE)
	{
		//error
		return new Card(0, 'N', HEART);
	}
	return _deck[_topOfDeck++];
}

/*
Creates the deck of 52 cards.
*/
void Deck::initDeck()
{
	int totalCards = 0;
	for (int i = 0; i < 4; i++) // Suits
	{
		for (int j = 2; j < 11; j++) // Values
		{
			_deck[totalCards] = new Card(j, 'N', (Suit)i);
			
			totalCards++;
		}

		//Add the face cards
		_deck[totalCards] = new Card(11, 'A', (Suit)i);
		totalCards++;
		_deck[totalCards] = new Card(10, 'J', (Suit)i);
		totalCards++;
		_deck[totalCards] = new Card(10, 'Q', (Suit)i);
		totalCards++;
		_deck[totalCards] = new Card(10, 'K', (Suit)i);
		totalCards++;
	}
}

//swaps the position of two cards in the deck
void Deck::swap(int index1, int index2)
{
	Card* temp;
	temp = _deck[index1];
	_deck[index1] = _deck[index2];
	_deck[index2] = temp;
}
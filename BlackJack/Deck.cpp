#include "Deck.h"
#include <iostream>
#include <random>
Deck::Deck()
{
	initDeck();
}


Deck::~Deck()
{
}

void Deck::shuffle()
{
	int cardsLeft = DECK_SIZE;
	rand();
}
Card Deck::draw()
{
	return{ 1, 'N', SPADE };
}

/*
Creates the deck of 52 cards.
*/
void Deck::initDeck()
{
	Card* _deck[DECK_SIZE];
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

	while (true)
	{

	}
}

//swaps the position of two cards in the deck
void swap(int index1, int index2)
{

}
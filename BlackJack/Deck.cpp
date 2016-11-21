#include "Deck.h"
#include <iostream>
Deck::Deck()
{
	initDeck();
}


Deck::~Deck()
{
}

void Deck::shuffle()
{

}
Card Deck::draw()
{

}

void Deck::initDeck()
{
	Card deck[52];
	int totalCards = 0;
	for (int i = 0; i < 4; i++) // Suits
	{
		for (int j = 2; j < 11; j++) // Values
		{
			deck[totalCards] = { j, 'N', (Suit) i};
			std::cout << deck[totalCards].suit << std::endl;
			totalCards++;
		}
		//Add ace, jack, queen, king
	}
}
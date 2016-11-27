#pragma once
/*
Card.h

The class for a normal card.

int _value: The value of the card. A King of Diamonds has value 10.
char _face: The face of the card. A King of Diamonds has face K.
Suit _suit: The suit of the card. A King of Diamonds has suit DIAMOND, or 2.

The suit does not actually matter in blackjack, but it is included for
player who wish to count cards to increase the skill of the game. 
It also makes the game feel more like a real game of blackjack.*/
enum Suit { HEART, SPADE, DIAMOND, CLUB };

class Card
{
public:
	Card();
	Card(int value, char face, Suit suit);
	Card(Card* card);
	~Card();

	void printCard();
	int getValue() { return _value; }
	char getFace() { return _face; }
	Suit getSuit() { return _suit; }

private:
	int _value;
	char _face; // J, Q, K, A. for all other values, N will be used.
	Suit _suit;
};
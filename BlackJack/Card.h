#pragma once
enum Suit { HEART, SPADE, DIAMOND, CLUB };

class Card
{
public:
	Card();
	Card(int value, char face, Suit suit);
	~Card();

	void printCard();

private:
	int _value;
	char _face; // J, Q, K, A. for all other values, N will be used.
	Suit _suit;
};
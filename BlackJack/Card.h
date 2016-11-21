#pragma once
enum Suit { HEART, SPADE, DIAMOND, CLUB };

struct Card
{
	int value;
	char face; // J, Q, K, A. for all other values, N will be used.
	Suit suit;
};
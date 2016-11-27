#include "Card.h"
#include <iostream>
Card::Card() :
	_value(0),
	_face('N'),
	_suit(HEART)
{
	//default constructor
	//the 0 of Hearts is used throughout the program as a sign that
	//the user is not where they should be
}
Card::Card(int value, char face, Suit suit) :
	_value(value),
	_face(face),
	_suit(suit)
{
	//printCard();
}

Card::~Card()
{

}

/*
Prints cards in the following format.
The (Value) of (Suit).
Such as:
The 6 of Hearts.
or
The King of Spades.
*/
void Card::printCard()
{
	std::cout << "The ";
	if (_face != 'N')
	{
		switch (_face)
		{
		case 'A':
			std::cout << "Ace of ";
			break;
		case 'J':
			std::cout << "Jack of ";
			break;
		case 'Q':
			std::cout << "Queen of ";
			break;
		case 'K':
			std::cout << "King of ";
			break;
		}
	}
	else
	{
		std::cout << _value << " of ";
	}

	switch (_suit)
	{
	case HEART:
		std::cout << "Hearts.";
		break;
	case SPADE:
		std::cout << "Spades.";
		break;
	case DIAMOND:
		std::cout << "Diamonds.";
		break;
	case CLUB:
		std::cout << "Clubs";
		break;
	}
	std::cout << std::endl;
}
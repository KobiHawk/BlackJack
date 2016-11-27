#include "DebugDeck.h"
#include <iostream>
#include <time.h>


DebugDeck::DebugDeck()
{
		srand(time(NULL));
		initDeck();
}


DebugDeck::~DebugDeck()
{
}

/*
void DebugDeck::initDeck()

Instead of placing all 52 cards into the deck, this function allows the user
to place whichever cards they want into the deck, in any order.

Unspecified slots are filled with the 0 of Hearts, a card that does not exist,
to make it clear once the game has gone outside the scope of the programmed cards.
*/
void DebugDeck::initDeck()
{
	int totalCards = 0;
	char charInput = 'Q';
	int valueInput = -1;
	int numCards = -1;
	std::cout << "Welcome to debug mode. You can customize the deck.\n"
		<< "Please enter the number of cards you would like to set." << std::endl;
	while (numCards < 1)
	{
		std::cin >> numCards;
	}
	for (totalCards; totalCards < numCards; totalCards++)
	{
		std::cout << "Please specify the value of card #" << totalCards << std::endl;
		std::cin >> valueInput;
		if (valueInput == 10)
		{
			std::cout << "Please specify the face of card #" << totalCards << std::endl;
			std::cin >> charInput;
		}
		else if (valueInput == 11)
		{
			charInput = 'A';
		}
		else
		{
			charInput = 'N';
		}

		//error checking
		while ((valueInput < 2) || (valueInput > 11))
		{
			std::cout << "Value was not acceptable. (Acceptable values are between 2 and 11)" << std::endl;
			std::cin >> valueInput;
		}
		while ((charInput != 'N') && (charInput != 'A') && (charInput != 'J') && (charInput != 'Q') && (charInput != 'K'))
		{
			std::cout << "Face value was not acceptable. (Acceptable values are J, Q, K, A, or N.)" << std::endl;
			std::cin >> charInput;
		}
		//end error checking

		_deck[totalCards] = new Card(valueInput, charInput, (Suit)(rand() % 4)); // rand() % 4, there are 4 suits, suit doesn't matter for blackjack so we don't bog the user down with choosing it
	}
	
	for (int i = totalCards; i < DECK_SIZE; i++)
	{
		_deck[i] = new Card(0, 'N', HEART); // fill the rest of the deck with hearts to prevent crashing. Only relevant if user forgets to load enough cards.
	}
}
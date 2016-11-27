#pragma once
#include "Deck.h"
/*
DebugDeck.h
Child of Deck

A deck used only for debug purposes.
You can program the deck to have whatever cards you want in it.
Debug mode is turned on via a compiler flag in Flags.h.
*/

class DebugDeck : public Deck
{
public:
	DebugDeck();
	~DebugDeck();

	void initDeck();
};


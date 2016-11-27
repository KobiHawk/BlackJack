#pragma once
#include "Deck.h"
#include "DebugDeck.h"
#include "Player.h"
#include "Dealer.h"
#include "Flags.h"

/*
Game.h

This class controls the logic of the game, and manages the player and deck.

A compiler flag is used to determine if the game is to be launched in debug mode. This is toggled in Flags.h.

DebugDeck _deck: If the game is in debug mode, loads a DebugDeck instead of a regular Deck.
Deck _deck: If the game is not in debug mode, loads a normal deck. This deck initializes a normal 52 card deck and has a shuffle function.
Player _player: The player.
Dealer _dealer: The dealer.
int _bet: The current bet. This is modified throughout the game if the player takes certain actions.
*/

static const int MIN_BET = 5;
static const int MAX_BET = 500;


class Game
{
public:
	Game();
	~Game();

	void playRound();
	void splitGame(Player* thePlayer);
	void resetGame();
	void displayHelpMessage();
	void endGame(Player* thePlayer);
	bool checkBust(Player* thePlayer);

	
private:
#ifdef _BLACKJACK_DEBUG
	DebugDeck _deck;
#else 
	Deck _deck;
#endif
	Player _player;
	Dealer _dealer;
	int _bet;
};


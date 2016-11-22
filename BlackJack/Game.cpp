#include "Game.h"
#include <iostream>


Game::Game() :
	_minBet(5),
	_maxBet(500)
{
}


Game::~Game()
{
}

void Game::playRound()
{
	//get bets
	std::cout << "How much would you like to bet?" << std::endl
		<< "Minimum bet: " << _minBet << std::endl
		<< "Maximum bet: " << _maxBet << std::endl;
	int bet = 0;
	while ((bet < _minBet) || (bet > _maxBet) || (bet > _player.getChips()))
	{
		std::cin >> bet;
	}

	//deal initial cards

	//loop: ask for hit, stay, split, double down, etc
	////check for bust

	//dealer actions: hit, stay
	////check for bust

	//resolve end of game, pay out
	//ask to play again? go back to top
}
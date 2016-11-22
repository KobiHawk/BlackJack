#include "Game.h"
#include <iostream>


Game::Game() :
	_minBet(5),
	_maxBet(500)
{
	playRound();
}


Game::~Game()
{
}

void Game::playRound()
{
	char gameLoop = 'Y';
	while (gameLoop == 'Y')
	{
		//get bets
		std::cout << "How much would you like to bet? You have " << _player.getChips() << " chips." << std::endl
			<< "Minimum bet: " << _minBet << std::endl
			<< "Maximum bet: " << _maxBet << std::endl;
		int bet = 0;
		while ((bet < _minBet) || (bet > _maxBet) || (bet > _player.getChips()))
		{
			std::cin >> bet;
		}

		//deal initial cards
		_player.drawCard(_deck.draw());
		_player.drawCard(_deck.draw());
		_dealer.drawCard(_deck.draw());
		_dealer.drawCard(_deck.draw());

		//loop: ask for hit, stay, split, double down, etc
		////check for bust
		bool continuePlaying = true;
		char input;

		while (continuePlaying)
		{
			std::cout << "Player cards: " << std::endl;
			_player.printHand();
			if (_player.getSum() <= 21)
			{
				std::cout << "Sum: " << _player.getSum() << ". Would you like to [H]it or [S]tay?" << std::endl;
				std::cin >> input;
				if (input == 'S')
				{
					continuePlaying = false;
				}
				else
				{
					_player.drawCard(_deck.draw());
				}
			}
			else
			{
				std::cout << "You have busted. Sum: " << _player.getSum() << std::endl;
				continuePlaying = false;
			}
		}

			std::cout << "Would you like to play again? [Y]es or [N]o?" << std::endl;
			std::cin >> gameLoop;
		//
	}
	//dealer actions: hit, stay
	////check for bust

	//resolve end of game, pay out
	//ask to play again? go back to top
}
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
	bool bust;
	while (gameLoop == 'Y')
	{
		//get game ready for a new round
		bust = false;
		resetGame();


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
			std::cout << std::endl;
			
			std::cout << "Dealer's card is: " << std::endl;
			_dealer.getRevealedCard()->printCard();
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
				bust = true;
				std::cout << "You have busted. Sum: " << _player.getSum() << std::endl;
				continuePlaying = false;
				_player.changeChips(-bet);
			}
		}

		//dealer actions: hit, stay
		////check for bust
		if (!bust)
		{
			while (_dealer.getSum() < 17)
			{
				std::cout << "Dealer hits." << std::endl;
				_dealer.drawCard(_deck.draw());
			}

			std::cout << "Dealer's hand: " << std::endl;
			_dealer.printHand();

			if (_dealer.getSum() > 21)
			{
				std::cout << "Dealer busts! Sum: " << _dealer.getSum() << ". You win!" << std::endl;
			}
			else if (_player.getSum() > _dealer.getSum())
			{
				std::cout << "Your sum: " << _player.getSum()
					<< ". Dealer's sum: " << _dealer.getSum()
					<< ". You win!" << std::endl;

				_player.changeChips(bet);
			}
			else if (_player.getSum() == _dealer.getSum())
			{
				std::cout << "Your sum: " << _player.getSum()
					<< ". Dealer's sum: " << _dealer.getSum()
					<< ". Game is tied." << std::endl;
			}
			else
			{
				std::cout << "Your sum: " << _player.getSum()
					<< ". Dealer's sum: " << _dealer.getSum()
					<< ". Dealer wins." << std::endl;

				_player.changeChips(-bet);
			}
		}



		//resolve end of game, pay out
		//ask to play again? go back to top
		if (_player.getChips() < _minBet)
		{
			std::cout << "You are out of chips. Thank you for playing." << std::endl;
			gameLoop = 'N';
		}
		else
		{
			std::cout << "Would you like to play again? [Y]es or [N]o?" << std::endl;
			std::cin >> gameLoop;
		}
	}
}

void Game::resetGame()
{
	int totalChips = _player.getChips();
	_player = Player(totalChips);
	_dealer = Dealer();
}
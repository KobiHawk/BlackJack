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


		bool continuePlaying = true;
		char input = 'Q';

		//check for blackjack
		if (_player.getSum() == 21)
		{
			_player.printHand();
			_player.setBlackjack(true);
			std::cout << "You got a blackjack! Payout increased by 1.5 times!" << std::endl;
			continuePlaying = false;
			bust = true; // we'll set this to true to skip the bust playout at the end
			bet *= 1.5;
		}
		if (_dealer.getSum() == 21)
		{
			_dealer.setBlackjack(true);
		}

		//loop: ask for hit, stay, split, double down, etc
		////check for bust


		while (continuePlaying) // get more cards/take more actions
		{
			_player.printHand();
			std::cout << std::endl;
			
			std::cout << "Dealer's revealed card is: " << std::endl;
			_dealer.getRevealedCard()->printCard();
			if (_player.getSum() <= 21)
			{
				std::cout << "Sum: " << _player.getSum() << ". Would you like to [H]it, [S]tay, S[P]lit, [D]ouble Down, or S[U]rrender? (Press E for H[E]lp.)" << std::endl;
				
				//get valid input
				while ((input != 'S') && (input != 'H') && (input != 'P') && (input != 'D') && (input != 'U') && (input != 'E'))
				{
					std::cin >> input;
				}

				switch(input)
				{
				case 'S': // stay
					continuePlaying = false;
					break;
				
				case 'H': // hit
					_player.drawCard(_deck.draw());
					break;

				case 'P': // split
					if (_player.checkSplit())
					{
						
					}
					else
					{
						//can't split
					}
					break;

				case 'D': // double down
					if ((_player.getChips() >= bet * 2) && (_player.getCards() == 2))
					{
						_player.drawCard(_deck.draw());
						_player.printHand();
						bet *= 2;
						std::cout << "Bet is now " << bet << std::endl;
						continuePlaying = false;
					}
					else
					{
						//player doesnt have enough chips to double down, or has more than 2 cards
					}
					break;

				case 'U': // surrender
					//should also add case for if player has blackjack
					if (_dealer.getRevealedCard()->getFace() == 'A')
					{
						_dealer.printHand();
						bust = true;
						continuePlaying = false;
						_player.changeChips(-(bet * 0.5));
					}
					else
					{
						//cant surrender
					}
					break;

				case 'E': // help
					displayHelpMessage();
					break;
				}
				input = 'Q';
			}
			else
			{
				continuePlaying = false;
			}
		}

		//check for player bust
		//If the player has an ace, and it being 11 would cause them to bust
		if (_player.getSum() > 21)
		{
			if (_player.getAces() < 1)
			{
				bust = true;
				std::cout << "You have busted. Sum: " << _player.getSum() << std::endl;
				_player.changeChips(-bet);
			}
			else //Then we ignore the ace for future bust checks and reduce the sum of their hand by 10 (A counting as 11 is now 1)
			{
				_player.changeAces(-1);
				_player.changeSum(-10);
			}
		}

		//dealer actions: hit, stay
		////check for bust
		if (_player.getBlackjack() == true)
		{
			_dealer.printHand();
			if (_dealer.getBlackjack() == true)
			{
				std::cout << "Both players have blackjack. Game is tied." << std::endl;
			}
			else
			{
				std::cout << "Player wins." << std::endl;
				_player.changeChips(bet);
			}
		}
		else if (!bust)
		{
			while (_dealer.getSum() < 17)
			{
				std::cout << "Dealer hits." << std::endl;
				_dealer.drawCard(_deck.draw());
			}

			_dealer.printHand();

			if (_dealer.getSum() > 21)
			{
				std::cout << "Dealer busts! Sum: " << _dealer.getSum() << ". You win!" << std::endl;
				_player.changeChips(bet); 
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
					<< ". Dealer's sum: " << _dealer.getSum();
					
				if (_dealer.getBlackjack() == false)
				{
					std::cout << ". Game is tied." << std::endl;
				}
				else
				{
					std::cout << ". Dealer has blackjack. Dealer wins." << std::endl;
					_player.changeChips(-bet);
				}
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

void Game::displayHelpMessage()
{
	std::cout << "[H]it will give you another card. If you go over 21, you will bust.\n"
		<< "[S]tay will cause you to keep your current hand. If it's higher than the dealer's \n"
		<< "hand, you will win. If it's lower, you will lose. If they are tied, no chips are affected.\n"
		<< "S[P]lit can only be used when your cards are the same (If you have two 8s, or two Jacks, but \n"
		<< "not a Jack and a Queen). You will split your hand into two hands of one card each and play \n"
		<< "them seperately. \n"
		<< "[D]ouble Down will give you only one more card, and you will double your bet. Can only \n"
		<< "be used when you have two cards. \n"
		<< "S[U]rrender can only be used when the dealer is showing an Ace. You will automatically lose \n"
		<< "the hand, but you will only lose half of your bet." << std::endl;
}

void Game::endGame()
{

}
#include "Game.h"
#include "DebugDeck.h"
#include <iostream>
#include <cctype>


Game::Game()
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
	int split;
	while (gameLoop == 'Y')
	{
		//get game ready for a new round
		bust = false;
		split = false;
		resetGame();

//we only want to shuffle in a normal game, not in debug mode
#ifndef _BLACKJACK_DEBUG
		_deck.shuffle();
#endif
		


		//get bets
		std::cout << "How much would you like to bet? You have " << _player.getChips() << " chips." << std::endl
			<< "Minimum bet: " << MIN_BET << std::endl
			<< "Maximum bet: " << MAX_BET << std::endl;
		_bet = 0;
		while ((_bet < MIN_BET) || (_bet > MAX_BET) || (_bet > _player.getChips()))
		{
			std::cin >> _bet;
		}

		//deal initial cards
		_player.drawCard(_deck.draw());
		_player.drawCard(_deck.draw());
		_dealer.drawCard(_deck.draw());
		_dealer.drawCard(_deck.draw());

		bool continuePlaying = true;

		//check for blackjack
		if (_player.getSum() == 21)
		{
			_player.printHand();
			_player.setBlackjack(true);
			std::cout << "You got a blackjack! Payout increased by 1.5 times!" << std::endl;
			continuePlaying = false;
			bust = true; // we'll set this to true to skip the bust playout at the end, since we know we're not busting
			_bet *= 1.5;
		}
		if (_dealer.getSum() == 21)
		{
			_dealer.setBlackjack(true);
		}


		
		char input = 'Q';

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
					input = toupper(input);
				}

				switch (input)
				{
				case 'S': // stay
					continuePlaying = false;
					break;

				case 'H': // hit
					_player.drawCard(_deck.draw());
					break;

				case 'P': // split
					if ((_player.checkSplit()) && (_player.getChips() > (_bet * 2)))
					{
						split = true;
						Player player1;
						Player player2;

						player1.drawCard(_player.getSpecificCard(0));
						player2.drawCard(_player.getSpecificCard(1));

						splitGame(&player1);
						splitGame(&player2);

						if (!checkBust(&player1))
						{
							endGame(&player1);
						}
						if (!checkBust(&player2))
						{
							endGame(&player2);
						}
						_player.changeChips((player1.getChips() - 100) + (player2.getChips() - 100)); // starting chip amount is 100

						continuePlaying = false;
					}
					else
					{
						//can't split
					}
					break;

				case 'D': // double down
					if ((_player.getChips() >= _bet * 2) && (_player.getCards() == 2))
					{
						_player.drawCard(_deck.draw());
						_player.printHand();
						_bet *= 2;
						std::cout << "Bet is now " << _bet << std::endl;
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
						_player.changeChips(-(_bet * 0.5));
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
			else // sum > 21, so they cant take more actions
			{
				bust = checkBust(&_player);
				if (bust)
				{
					continuePlaying = false;
				}
			}
		}

		if (!split)
		{
			//check for player bust

			//check blackjack
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
					_player.changeChips(_bet);
				}
			}
			else if (!bust)
			{
				endGame(&_player);
			}
		}


		//resolve end of game, pay out
		//ask to play again? go back to top
		if (_player.getChips() < MIN_BET)
		{
			std::cout << "You are out of chips. Thank you for playing." << std::endl;
			gameLoop = 'N';
		}
		else
		{
			std::cout << "Would you like to play again? [Y]es or [N]o?" << std::endl;
			std::cin >> gameLoop;
			gameLoop = toupper(gameLoop);
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

void Game::splitGame(Player* thePlayer)
{
	//player has decided to split their pair, can only hit or stay after splitting
	char input = 'Q';
	bool continuePlaying = true;

	while (continuePlaying) // get more cards/take more actions
	{
		thePlayer->printHand();
		std::cout << std::endl;

		std::cout << "Dealer's revealed card is: " << std::endl;
		_dealer.getRevealedCard()->printCard();
		if (thePlayer->getSum() <= 21)
		{
			std::cout << "Sum: " << thePlayer->getSum() << ". Would you like to [H]it or [S]tay? (Press E for H[E]lp.)" << std::endl;

			//get valid input
			while ((input != 'S') && (input != 'H') && (input != 'E'))
			{
				std::cin >> input;
				input = toupper(input);
			}

			switch (input)
			{
			case 'S': // stay
				continuePlaying = false;
				break;

			case 'H': // hit
				thePlayer->drawCard(_deck.draw());
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
}

void Game::endGame(Player* thePlayer)
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
		thePlayer->changeChips(_bet);
	}
	else if (_player.getSum() > _dealer.getSum())
	{
		std::cout << "Your sum: " << thePlayer->getSum()
			<< ". Dealer's sum: " << _dealer.getSum()
			<< ". You win!" << std::endl;

		thePlayer->changeChips(_bet);
	}
	else if (_player.getSum() == _dealer.getSum())
	{
		std::cout << "Your sum: " << thePlayer->getSum()
			<< ". Dealer's sum: " << _dealer.getSum();

		if (_dealer.getBlackjack() == false)
		{
			std::cout << ". Game is tied." << std::endl;
		}
		else
		{
			std::cout << ". Dealer has blackjack. Dealer wins." << std::endl;
			thePlayer->changeChips(-_bet);
		}
	}
	else
	{
		std::cout << "Your sum: " << thePlayer->getSum()
			<< ". Dealer's sum: " << _dealer.getSum()
			<< ". Dealer wins." << std::endl;

		thePlayer->changeChips(-_bet);
	}
}

bool Game::checkBust(Player* thePlayer)
{
	bool result = false;
	if (thePlayer->getSum() > 21)
	{
		if (thePlayer->getAces() < 1)
		{
			result = true;
			std::cout << "You have busted. Sum: " << thePlayer->getSum() << std::endl;
			thePlayer->changeChips(-_bet);
		}
		else //Then we ignore the ace for future bust checks and reduce the sum of their hand by 10 (A counting as 11 is now 1)
		{
			thePlayer->changeAces(-1);
			thePlayer->changeSum(-10);
		}
	}

	return result;
}
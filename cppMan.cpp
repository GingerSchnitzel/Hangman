#include "cppMan.h"
#include <string>
#include <vector>
#include <random>

namespace WordList
{
	const std::vector<std::string> words{ "mystery", "broccoli" , "account", "almost", "spaghetti", "opinion", "beautiful", "distance",
									  "luggage", "airplane", "apple", "banana", "cherry", "platipus", "elephant", "mammoth", "applause" };

	const std::string& makeRandomWord()
	{
		static std::random_device rd{};                                                 // Random device for seeding the twister
		static std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };      // std::seed_seq resolves underseeding issues 
		static std::mt19937 engine(ss);                                                 // seeding the random engine with the random data
		static std::uniform_int_distribution<size_t> dist(0, words.size() - 1);         // generated random integers withing specified range
		size_t randomIndex = dist(engine);                                              // generated a random integer withing the set range and stores it in randomIndex
		// all made static in order not to create objects all over again when function is called
		return words[randomIndex];
	}
	//Create a class named Session that will be used to store all of the data the game needs to manage in a game session.For now, we just need to know what the random word is.
	//Create a function to display the basic state of the game, where the word is displayed as underscores.
	//Create a function to accept a letter of input from the user.
	//Do basic input validation to filter out non - letters or extraneous input.
}

bool playAgain()
{
	std::cout << "Would you like to play again?";
	std::string answer;

	while (true)
	{
		std::cout << " y/n? ";

		std::getline(std::cin, answer);

		if (answer.length() != 1)
		{
			continue;
		}

		switch (answer[0])
		{
		case 'y':
		case'Y':
			std::cout << '\n';
			return true;

		case 'N':
		case'n':

			std::cout << "Thank you for playing! \n";
			return false;
		}
	}
}

Session::Session()
	: _randomWord{ WordList::makeRandomWord() },
	underscoreContainer{ _randomWord },
	correctGuessedContainer{},
	incorrectGuessedContainer{},
	guesses{},
	guessesLeft{ 6 }
{
}

 void Session::printContainers(const std::vector<char>& vec)
{
	for (const auto& element : vec)
	{
		std::cout << element;
	}
	std::cout << '\n';
}

 const std::string& Session::getRandomWord()
{
	return _randomWord;
}

 void Session::displayGame()
{
	size_t initialIncorrectSize{ incorrectGuessedContainer.size() };

	if (firstGameRun)
	{
		std::cout << "The word is: "s;
		for (size_t i{ 0 }; i < underscoreContainer.size(); ++i)
		{
			underscoreContainer[i] = '_';
			std::cout << underscoreContainer[i];
		}
		std::cout << '\n';
	}
	firstGameRun = false;
	//std::cout << '\n';

	if (!firstGameRun)
	{
		char userGuess = getGuess();
		std::cout << "The word is: "s;
		for (size_t j{ 0 }; j < _randomWord.size(); ++j)
		{

			if (userGuess == _randomWord[j])
			{
				underscoreContainer[j] = _randomWord[j];

				if (!hasLetters(userGuess, correctGuessedContainer))
				{
					//guesses.push_back(underscoreContainer[j]);
					correctGuessedContainer.push_back(underscoreContainer[j]); // if the letter is more than 1 time in the container, it introduces it twice
				}

			}
			else if (j == (_randomWord.size() - 1))
			{
				if (!hasLetters(userGuess, correctGuessedContainer) && !hasLetters(userGuess, incorrectGuessedContainer))
				{
					//guesses.push_back(underscoreContainer[j]);
					incorrectGuessedContainer.push_back(userGuess); // introduces even correct letters
				}
			}
			std::cout << underscoreContainer[j];

		}
		std::cout << '\n';

		if (incorrectGuessedContainer.size() > initialIncorrectSize)
		{
			std::cout << "Your guess was incorrect. Try again.\n";
			std::cout << '\n';
		}
		//prints even if the letter is correct
	}

}

 bool Session::hasLetters(const char& letter, std::vector<char> container) // MAYBE IT SHOULD BE MOVED OUT OF HERE SINCE IT DOESN'T USE DATA MEMBERS??
{
	for (size_t i{ 0 }; i < container.size(); ++i)
	{
		if (letter == container[i])
		{

			return true;
		}
	}
	//container.push_back(letter); // IF IT INTRODUCES LETTERS TOO, IT DOESN'T HAVE A SINGLE RESPONSABILITY
	return false;
}

 void Session::printGuesses()
{
	std::cout << "Guesses left: ";
	if (firstGameRun)
	{
		for (size_t i{ 0 }; i < guessesLeft; ++i)
		{
			guesses.push_back('+');
			std::cout << guesses[i];
		}
		std::cout << '\n';
	}
	if (!firstGameRun)
	{
		for (size_t z{ 0 }; z < incorrectGuessedContainer.size(); ++z)
		{
			guesses[z] = incorrectGuessedContainer[z];
		}

		for (size_t j{ 0 }; j < guesses.size(); ++j)
		{
			std::cout << guesses[j];
		}
		std::cout << '\n';
	}
}

 char Session::getGuess()
{

	while (true)
	{
		std::cout << "Enter your next letter: "s;
		char c{};
		std::cin >> c;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "That wasn't a valid input.  Try again.\n"s;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (c < 'a' || c > 'z')
		{
			std::cout << "That wasn't a valid input.  Try again.\n"s;
			continue;
		}

		if (hasLetters(c, incorrectGuessedContainer) || hasLetters(c, correctGuessedContainer))
		{
			std::cout << "Letter already guessed. Try again.\n"s;
			continue;
		}

		return c;
	}

}

 void Session::playCppMan()
{
	std::cout << "Welcome to C++man (a variant of Hangman)\n"s;
	std::cout << "To win: guess the word.  To lose: run out of pluses.\n"s << '\n';

	while (true)
	{
		printGuesses();
		displayGame();
		if (_randomWord == underscoreContainer)
		{
			std::cout << "You have won. Congrats! \n";
			break;
		}
		if (incorrectGuessedContainer.size() == guessesLeft)
		{
			std::cout << "You have lost! The word was: " << _randomWord << '!' << '\n';
			break;
		}
	}

}

 void Session::playHangMan()
{

	std::cout << "Welcome to Hangman!\n"s;
	std::cout << "To win: guess the word.  To lose: run out of guesses.\n"s << '\n';
	while (true)
	{
		displayGame();
		switch (incorrectGuessedContainer.size())
		{
		case 0:
			std::cout << "  ____" << '\n';
			std::cout << " |  " << '\n';
			std::cout << " |  " << '\n';
			std::cout << " |  " << '\n';
			std::cout << "_|_" << '\n' << '\n';
			break;

		case 1:
			std::cout << "  ____" << '\n';
			std::cout << " |   0" << '\n';
			std::cout << " |  " << '\n';
			std::cout << " |  " << '\n';
			std::cout << "_|_" << '\n' << '\n';
			break;

		case 2:
			std::cout << "  ____" << '\n';
			std::cout << " |  \\0" << '\n';
			std::cout << " |  " << '\n';
			std::cout << " |  " << '\n';
			std::cout << "_|_" << '\n' << '\n';
			break;

		case 3:
			std::cout << "  ____" << '\n';
			std::cout << " |  \\0/" << '\n';
			std::cout << " |  " << '\n';
			std::cout << " |  " << '\n';
			std::cout << "_|_" << '\n' << '\n';
			break;

		case 4:
			std::cout << "  ____" << '\n';
			std::cout << " |  \\0/" << '\n';
			std::cout << " |   |" << '\n';
			std::cout << " |  " << '\n';
			std::cout << "_|_" << '\n' << '\n';
			break;

		case 5:
			std::cout << "  ____" << '\n';
			std::cout << " |  \\0/" << '\n';
			std::cout << " |   |" << '\n';
			std::cout << " |  /" << '\n';
			std::cout << "_|_ " << '\n' << '\n';
			break;

		case 6:
			std::cout << "  ____" << '\n';
			std::cout << " |  \\0/" << '\n';
			std::cout << " |   |" << '\n';
			std::cout << " |  / \\" << '\n';
			std::cout << "_|_ " << '\n' << '\n';
			break;
		}
		printContainers(incorrectGuessedContainer);
		std::cout << "------" << '\n' << '\n';
		if (_randomWord == underscoreContainer)
		{
			std::cout << "You have won. Congrats! \n";
			break;
		}
		if (incorrectGuessedContainer.size() == guessesLeft)
		{
			std::cout << "You have lost! The word was: " << _randomWord << '!' << '\n';
			break;
		}
	}
}

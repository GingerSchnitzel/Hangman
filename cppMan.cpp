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



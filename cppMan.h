#ifndef CPPMAN_H
#define CPPMAN_H
#include <vector>
#include <string>
#include <iostream>

using namespace std::string_literals;

namespace WordList
{
	const std::string& makeRandomWord();
}
bool playAgain();

class Session
{
private:
	std::string _randomWord;
	std::string underscoreContainer;
	std::vector<char> correctGuessedContainer;
	std::vector<char> incorrectGuessedContainer;
	std::vector<char> guesses;
	int32_t guessesLeft;
	static inline bool firstGameRun{ true };
public:
	Session();
	void printContainers(const std::vector<char>& vec);
	const std::string& getRandomWord();
	void displayGame();
	bool hasLetters(const char& letter, std::vector<char> container);
	void printGuesses();
	char getGuess();
	void playCppMan();
	void playHangMan();

};


//Update the Session class to track which letters have been guessed so far.                        DONE
//Modify the game state function to display both underscores and correctly guessed letters.        DONE
//Update the input routine to reject letters that have already been guessed.                       DONE??
//Write a loop that executes 6 times before quitting(so we can test the above).






#endif
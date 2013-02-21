#include "letter_provider.hpp"

char* LetterProvider::letters[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "qu", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

LetterProvider* LetterProvider::instance = NULL;

LetterProvider::LetterProvider()
{
	//seed random
	std::srand(std::time(0));
}

char* LetterProvider::_getNextLetter( int column_index )
{
	unsigned int index = std::rand() % 26;
	return letters[index];
}

void LetterProvider::checkCreateInstance()
{
	if (instance == NULL) {
		instance = new LetterProvider();
	}
}

char* LetterProvider::getNextLetter( int column_index )
{
	checkCreateInstance();
	return instance->_getNextLetter(column_index);
}




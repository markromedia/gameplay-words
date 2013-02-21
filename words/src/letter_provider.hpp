#ifndef __LETTER_PROVIDER__hpp
#define __LETTER_PROVIDER__hpp

#include <cstdlib>
#include <iostream>
#include <ctime>

class LetterProvider {
private:
	/// Default constructor.
	LetterProvider();

	/// Check create instance.
	static void checkCreateInstance();

	/// @summary	The letters.
	static char* letters[26];

	/// @summary	The instance.
	static LetterProvider* instance;

	/// Gets the next letter.
	/// @param	column_index	Zero-based index of the column.
	/// @return	null if it fails, else the next letter.
	char* _getNextLetter(int column_index);
public:
	/// Gets the next letter and moves the column pointer up
	/// @param	column_index	Zero-based index of the column.
	/// @return	null if it fails, else the next letter.
	static char* getNextLetter(int column_index);
};

#endif  // __LETTER_PROVIDER__hpp
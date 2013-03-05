#ifndef __WORD_CHECKER__hpp
#define __WORD_CHECKER__hpp

#include <vector>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <iostream>

#include "hunspell/hunspell.hxx"
#include "gameplay.h"
#include "perf-solver/boggle_solver.h"

#include "board.hpp"
#include "letter_provider.hpp"

class Dictionary {
private:
	/// @summary	The handle to the hunspell.
	Hunspell* handle;

	/// @summary	The singleon instance.
	static Dictionary* instance;

	//the locations of the dictionaries
	static const char* dictionary_file;
	static const char* affix_file;

	/// @summary	The actual dictionary
	std::vector<std::string*> dictionary;

	/// Character to int.
	/// @param [in,out]	str	If non-null, the.
	/// @return	.
	static int charToInt(char* str);

	/// Reads a word from file and adds it to dictionary.
	/// @param [in,out]	dict_file	If non-null, the dictionary file.
	/// @return	true if it succeeds, false if it fails.
	static bool addWordToDictionary(FILE* dict_file);
public:
	/// Initialises this object.
	static void Init();

	/// Query if 'str' is word.
	/// @param [in,out]	str	If non-null, the.
	/// @return	true if word, false if not.
	static bool IsWord(const char* str);

	/// Builds the dictionary.
	static void BuildDictionary();
};

#endif  // __WORD_CHECKER__hpp
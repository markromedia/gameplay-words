#ifndef __WORD_CHECKER__hpp
#define __WORD_CHECKER__hpp

#include <vector>

#include "hunspell/hunspell.hxx"

class WordChecker {
private:
	/// @summary	The handle to the hunspell.
	Hunspell* handle;

	/// @summary	The singleon instance.
	static WordChecker* instance;

	//the locations of the dictionaries
	static const char* dictionary_file;
	static const char* affix_file;
public:
	/// Initialises this object.
	static void Init();

	/// Query if 'str' is word.
	/// @param [in,out]	str	If non-null, the.
	/// @return	true if word, false if not.
	static bool IsWord(const char* str);
};

#endif  // __WORD_CHECKER__hpp
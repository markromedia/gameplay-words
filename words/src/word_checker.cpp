#include "word_checker.hpp"

//init static vars
WordChecker* WordChecker::instance = NULL;

//the location of the dictionaries
const char* WordChecker::dictionary_file = "res/dict/en_US.dic";
const char* WordChecker::affix_file = "res/dict/en_US.aff";


void WordChecker::Init()
{
	instance = new WordChecker();

	//init hunspell
	instance->handle = new Hunspell(affix_file, dictionary_file);
}

bool WordChecker::IsWord(const char* str )
{
	return instance->handle->spell(str) != 0;
}

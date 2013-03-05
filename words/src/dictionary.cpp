#include "dictionary.hpp"

//init static vars
Dictionary* Dictionary::instance = NULL;

//the location of the dictionaries
const char* Dictionary::dictionary_file = "res/dict/en_US.dic";
const char* Dictionary::affix_file = "res/dict/en_US.aff";


void Dictionary::Init()
{
	instance = new Dictionary();

	long start_time = gameplay::Game::getInstance()->getAbsoluteTime();

	//init hunspell
	instance->handle = new Hunspell(affix_file, dictionary_file);

	long endTime = gameplay::Game::getInstance()->getAbsoluteTime();
	std::ostringstream oss;
	oss << "Hunspell Building time: " << endTime - start_time << "ms\n";
	gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, oss.str().c_str());

	//build internal dictionary
	BuildDictionary();
}

bool Dictionary::IsWord(const char* str )
{
	return instance->handle->spell(str) != 0;
}

void Dictionary::BuildDictionary()
{
	
	//the total # of words we'll be dealing with
	int word_count = 0;
	//buffer that stores each line read from the dictionary
	char buffer[100];
	
	//create handles to the dictionaries
	FILE* english_dict = gameplay::FileSystem::openFile(dictionary_file, "r");;
	
	//go through our list of dictionaries and grab the first line to get # of words in it
	fgets(buffer, 100, english_dict);	
	word_count += charToInt(buffer);

	//allocate the dictionary now
	instance->dictionary.reserve(word_count);

	//read file and add it to the dictionary
	while(addWordToDictionary(english_dict)) {}

	//sort our dictionary
	std::sort(instance->dictionary.begin(), instance->dictionary.end());

	//close our handles
	if (english_dict) {
		fclose(english_dict);
	}

	//create the solver
	BoggleSolver* solver = BoggleSolver::Create(44, "res/dict/dictionary.txt");
	
	long start_time = gameplay::Game::getInstance()->getAbsoluteTime();

	for (int i = 0; i < 2500; i++) {
		Board::CreateNewBoard();

		std::ostringstream oss;
		for (int i = 3; i >= 0; i--) {
			BoardColumn* col = Board::Columns()[i];
			for (int j = 0; j < 4; j++) {
				BoardCell* cell = col->cells[j];
				std::string letter = cell->letter;
				oss << letter;
				LetterProvider::ReturnLetter(letter);
			}
		}

		int score = solver->Score(oss.str().c_str());
		int c_count = BoggleSolver::WordCount;

		//long endTime = gameplay::Game::getInstance()->getAbsoluteTime();
		//std::ostringstream oss2;
		//oss2 << "Solving Time: " << endTime - start_time << "ms [" << oss.str() << ": " << c_count << "]\n";
		//gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, oss2.str().c_str());
	}
	long endTime = gameplay::Game::getInstance()->getAbsoluteTime();
	std::ostringstream oss2;
	oss2 << "Solving Time: " << endTime - start_time <<  "\n";
	gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, oss2.str().c_str());
}

int Dictionary::charToInt( char* str )
{
	std::stringstream stream;
	int index = 0;
	while (!(str[index] == '\n' || str[index] == '\0')) {
		stream << str[index];
		index++;
	}
	//write stream to index and return it
	stream >> index;
	return index;
}

bool Dictionary::addWordToDictionary(FILE* dict_file) {
	char buffer[100];
	
	if (fgets(buffer, 100, dict_file) == NULL) {
		return false;
	}	

	std::stringstream stream;
	int index = 0;
	while (!(buffer[index] == '\n' || buffer[index] == '\0' || buffer[index] == '/')) {
		stream << buffer[index];
		index++;
	}

	std::string str = stream.str();
	std::transform(str.begin(), str.end(),str.begin(), ::toupper);

	//copy string into heap
	instance->dictionary.push_back(new std::string(str));
	
	return true;
}

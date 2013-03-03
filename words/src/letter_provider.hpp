#ifndef __LETTER_PROVIDER__hpp
#define __LETTER_PROVIDER__hpp

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
#include <queue>
#include <iostream>

#include "gameplay.h"

class Dice {
private:
	/// @summary	The of this dice.
	std::vector<std::string> sides;
    
    ///the assigned letter
    std::string assigned_letter;
public:
	Dice(std::string s1, std::string s2, std::string s3, std::string s4, std::string s5, std::string s6);

	/// Gets a letter from the dice.
	/// @return	The letter.
	std::string getRandomLetter();
    
    ///assigns a letter to this dice
    void assignLetter();
    
    std::string getAssignedLetter();
};

class LetterProvider {
public:
    enum Mode { COLUMN, FIXED25 };
    
    //set the mode
    static void SetMode(Mode mode);
    
    //inits the letter provider with all its modes
    static void Init();
    
    /// returns a letter back to the pool
    static void ReturnLetter(std::string letter);
    
	/// Builds the columns. Will make columns with 100 entries each
    void BuildColumns();
    
    /// builds the fixed 25
    void BuildFixed25();
    
	/// Gets the next letter and moves the column pointer up
	/// @param	column_index	Zero-based index of the column.
	/// @return	null if it fails, else the next letter.
	static std::string getNextLetter(int column_index);
private:
	/// Default constructor.
	LetterProvider();

	/// Check create instance.
	static void checkCreateInstance();

	/// @summary	The letters.
	static std::string letters[26];

	/// @summary	The instance.
	static LetterProvider* instance;

	/// Gets the next letter.
	/// @param	column_index	Zero-based index of the column.
	/// @return	null if it fails, else the next letter.
	std::string _getNextLetter(int column_index);

	/// @summary	The dice.
	std::vector<Dice*> dice;

	/// @summary	The available dice.
	std::vector<Dice*> available_dice;
    
    /// @summary	The dice in use.
	std::vector<Dice*> dice_in_use;

	/// @summary	The columns.
	std::queue<std::string> columns[4];

	/// @summary	stores the index of each column
	int column_index[4];
    
    // the mode 
    LetterProvider::Mode mode;

};

#endif  // __LETTER_PROVIDER__hpp
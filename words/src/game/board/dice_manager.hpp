#ifndef __LETTER_PROVIDER__hpp
#define __LETTER_PROVIDER__hpp

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
#include <queue>
#include <iostream>
#include <map>

#include "gameplay.h"
#include "../../ext/solver_worker.hpp"

class DiceManager;

class Dice {
friend class DiceManager;
private:
public:
	Dice(int id, std::string s1, std::string s2, std::string s3, std::string s4, std::string s5, std::string s6);

	/// @summary	The of this dice.
	std::vector<std::string> sides;

	/// @summary	The identifier of this dice.
	int id;

	/// Gets a letter from the dice.
	/// @return	The letter.
	std::string getRandomLetter();
    
    ///assigns a letter to this dice
    void roll();

	/// Gets the assigned letter.
	/// @return	The assigned letter.
	std::string getAssignedLetter();

	/// @summary	Zero-based index of the side.
	unsigned int side_index;
};

class DiceManager {
public:
    //inits the letter provider with all its modes
    static void Init();
    
    /// returns a die back to the pool
    static void ReturnDie(Dice* die);
    
    /// builds the fixed 16
    static void ReassignDice();
    
	/// Gets an unused die
	static Dice* GetRandomDie();

	/// Gets a dice by identifier.
	/// @param	id	The identifier.
	/// @return	null if it fails, else the dice by identifier.
	static Dice* GetDieById(int id);

	/// @summary	The dice.
	static std::vector<Dice*> dice;
private:
	/// Default constructor.
	DiceManager();

	/// Check create instance.
	static void checkCreateInstance();

	/// @summary	The letters.
	static std::string letters[26];

	/// @summary	The instance.
	static DiceManager* instance;

	/// @summary	The available dice.
	std::vector<Dice*> available_dice;
    
	std::map<int, Dice*> dice_map;
};

#endif  // __LETTER_PROVIDER__hpp
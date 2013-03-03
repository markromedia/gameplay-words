#include "letter_provider.hpp"

std::string LetterProvider::letters[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "qu", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

LetterProvider* LetterProvider::instance = NULL;


Dice::Dice( std::string s1, std::string s2, std::string s3, std::string s4, std::string s5, std::string s6 )
{
	this->sides.push_back(s1);
	this->sides.push_back(s2);
	this->sides.push_back(s3);
	this->sides.push_back(s4);
	this->sides.push_back(s5);
	this->sides.push_back(s6);
}

std::string Dice::getRandomLetter()
{
	return this->sides[std::rand() % 6];
}

void Dice::assignLetter() {
    int idx = std::rand() % 6;
    this->assigned_letter = this->sides[idx];
}

std::string Dice::getAssignedLetter()
{
	return this->assigned_letter;
}

LetterProvider::LetterProvider()
{
	//seed random
	std::srand((unsigned int)std::time(NULL));

	//init the dice
	this->dice.push_back(new Dice("a", "a", "a", "f", "r", "s" ));
	this->dice.push_back(new Dice("a", "e", "e", "g", "m", "u" ));
	this->dice.push_back(new Dice("c", "e", "i", "i", "l", "t" ));
	this->dice.push_back(new Dice("d", "h", "l", "n", "o", "r" ));
	this->dice.push_back(new Dice("f", "i", "p", "r", "s", "y" ));
	this->dice.push_back(new Dice("a", "a", "e", "e", "e", "e" ));
	this->dice.push_back(new Dice("a", "e", "g", "m", "n", "n" ));
	this->dice.push_back(new Dice("c", "e", "i", "l", "p", "t" ));
	this->dice.push_back(new Dice("d", "d", "l", "n", "o", "r" ));
	this->dice.push_back(new Dice("g", "o", "r", "r", "v", "w" ));
	this->dice.push_back(new Dice("a", "a", "f", "i", "r", "s" ));
	this->dice.push_back(new Dice("a", "f", "i", "r", "s", "y" ));
	this->dice.push_back(new Dice("c", "e", "i", "l", "s", "t" ));
	this->dice.push_back(new Dice("e", "i", "i", "i", "t", "t" ));
	this->dice.push_back(new Dice("h", "i", "p", "r", "r", "y" ));
	this->dice.push_back(new Dice("a", "d", "e", "n", "n", "n" ));
	this->dice.push_back(new Dice("b", "j", "k", "qu", "x", "z" ));
	this->dice.push_back(new Dice("d", "h", "h", "n", "o", "t" ));
	this->dice.push_back(new Dice("e", "m", "o", "t", "t", "t" ));
	this->dice.push_back(new Dice("n", "o", "o", "t", "u", "w" ));
	this->dice.push_back(new Dice("a", "e", "e", "e", "e", "m" ));
	this->dice.push_back(new Dice("c", "c", "n", "s", "t", "w" ));
	this->dice.push_back(new Dice("d", "h", "h", "l", "o", "r" ));
	this->dice.push_back(new Dice("e", "n", "s", "s", "s", "u" ));
	this->dice.push_back(new Dice("o", "o", "o", "t", "t", "u" ));
}

void LetterProvider::Init() {
    instance = new LetterProvider();
    
    instance->BuildColumns();
    instance->BuildFixed25();
}

void LetterProvider::ReturnLetter(std::string letter) {
    if (instance->mode == FIXED25) {
        for (int i = 0; i < instance->dice_in_use.size(); i++) {
            if (instance->dice_in_use[i]->getAssignedLetter() == letter) {
                instance->available_dice.push_back(instance->dice_in_use[i]);
                instance->dice_in_use.erase(instance->dice_in_use.begin() + i);
                return;
            }
        }
    }
}

void LetterProvider::BuildColumns()
{
    for (int i = 0; i < 25; i++) {
		//copy 25 dice from all dice into available
		available_dice = dice;
		//grab 16 dice
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int dice_idx = std::rand() % available_dice.size();
				columns[i].push(available_dice[dice_idx]->getRandomLetter());
				available_dice.erase(available_dice.begin() + dice_idx);
			}
		}
	}
}

void LetterProvider::BuildFixed25() {
    //copy 25 dice from all dice into available
    available_dice = dice;

    for (int i = 0; i < 25; i++) {
        available_dice[i]->assignLetter();
	}
}

void LetterProvider::checkCreateInstance()
{
	if (instance == NULL) {
		instance = new LetterProvider();
	}
}

std::string LetterProvider::_getNextLetter( int column_index )
{
    switch (instance->mode) {
        case COLUMN: {
            std::string letter = instance->columns[column_index].front();
            instance->columns[column_index].pop();
            return letter;
        }
        case FIXED25: {
            int dice_idx = std::rand() % available_dice.size();
            Dice* dice = available_dice[dice_idx];
            //reassign the dices value
            dice->assignLetter();
            std::string letter = dice->getAssignedLetter();
            dice_in_use.push_back(dice);
            available_dice.erase(available_dice.begin() + dice_idx);
            return letter;
        }
    }
    return "";
}


std::string LetterProvider::getNextLetter( int column_index )
{
	checkCreateInstance();
	return instance->_getNextLetter(column_index);
}

void LetterProvider::SetMode(Mode mode) {
    instance->mode = mode;
}





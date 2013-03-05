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
	this->dice.push_back(new Dice("a", "a", "e", "e", "g", "n" ));
	this->dice.push_back(new Dice("e", "l", "r", "t", "t", "y" ));
	this->dice.push_back(new Dice("a", "o", "o", "t", "t", "w" ));
	this->dice.push_back(new Dice("a", "b", "b", "j", "o", "o" ));
	this->dice.push_back(new Dice("e", "h", "r", "t", "v", "w" ));
	this->dice.push_back(new Dice("c", "i", "m", "o", "t", "u" ));
	this->dice.push_back(new Dice("d", "i", "s", "t", "t", "y" ));
	this->dice.push_back(new Dice("e", "i", "o", "s", "s", "t" ));
	this->dice.push_back(new Dice("d", "e", "l", "r", "v", "y" ));
	this->dice.push_back(new Dice("a", "c", "h", "o", "p", "s" ));
	this->dice.push_back(new Dice("h", "i", "m", "n", "a", "u" ));
	this->dice.push_back(new Dice("e", "e", "i", "n", "s", "u" ));
	this->dice.push_back(new Dice("e", "e", "g", "h", "n", "a" ));
	this->dice.push_back(new Dice("a", "f", "f", "k", "p", "s" ));
	this->dice.push_back(new Dice("h", "l", "n", "n", "r", "z" ));
	this->dice.push_back(new Dice("d", "e", "i", "l", "r", "x" ));
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

    for (int i = 0; i < 16; i++) {
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





#include "letter_provider.hpp"

std::string DiceManager::letters[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "qu", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

DiceManager* DiceManager::instance = NULL;
std::vector<Dice*> DiceManager::dice;

Dice::Dice( int id, std::string s1, std::string s2, std::string s3, std::string s4, std::string s5, std::string s6 )
{
	this->id = id;
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

void Dice::roll() {
    int idx = std::rand() % 6;
	this->side_index = idx;
}

std::string Dice::getAssignedLetter()
{
	return this->sides[side_index];
}

DiceManager::DiceManager()
{
	//seed random
	std::srand((unsigned int)std::time(NULL));

	//init the dice
	dice.push_back(new Dice(1,  "a", "a", "e", "e", "g", "n" ));
	dice.push_back(new Dice(2,  "e", "l", "r", "t", "t", "y" ));
	dice.push_back(new Dice(3,  "a", "o", "o", "t", "t", "w" ));
	dice.push_back(new Dice(4,  "a", "b", "b", "j", "o", "o" ));
	dice.push_back(new Dice(5,  "e", "h", "r", "t", "v", "w" ));
	dice.push_back(new Dice(6,  "c", "i", "m", "o", "t", "u" ));
	dice.push_back(new Dice(7,  "d", "i", "s", "t", "t", "y" ));
	dice.push_back(new Dice(8,  "e", "i", "o", "s", "s", "t" ));
	dice.push_back(new Dice(9,  "d", "e", "l", "r", "v", "y" ));
	dice.push_back(new Dice(10, "a", "c", "h", "o", "p", "s" ));
	dice.push_back(new Dice(11, "h", "i", "m", "n", "a", "u" ));
	dice.push_back(new Dice(12, "e", "e", "i", "n", "s", "u" ));
	dice.push_back(new Dice(13, "e", "e", "g", "h", "n", "a" ));
	dice.push_back(new Dice(14, "a", "f", "f", "k", "p", "s" ));
	dice.push_back(new Dice(15, "h", "l", "n", "n", "r", "z" ));
	dice.push_back(new Dice(16, "d", "e", "i", "l", "r", "x" ));

	//add them to a map by their id
	for (unsigned int i = 0; i < dice.size(); i++) {
		dice_map[dice[i]->id] = dice[i];
	}
}

Dice* DiceManager::GetDieById( int id )
{
	Dice* die = instance->dice_map[id];
	//make sure this is marked as unavailable
	instance->dice_in_use.push_back(die);
	std::vector<Dice*>::iterator position = std::find(instance->available_dice.begin(), instance->available_dice.end(), die);
	if (position != instance->available_dice.end()) {
		instance->available_dice.erase(position);
	}

	return die;
}

void DiceManager::Init() {
    instance = new DiceManager();
}

void DiceManager::ReturnDie(Dice* die) {
    std::stringstream ss;
    ss << die->id << "\n";

    gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, "returning a die: ");
    gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, ss.str().c_str());
    
    for (unsigned int i = 0; i < instance->dice_in_use.size(); i++) {
        if (instance->dice_in_use[i]->id == die->id) {
            gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, "SUCCESS\n");
            Dice* die = instance->dice_in_use[i];
            instance->available_dice.push_back(die);
            instance->dice_in_use.erase(instance->dice_in_use.begin() + i);
            return;
        }
    }
    
    int failed_to_return = 1;
}

void DiceManager::ReassignDice() {
    //copy 16 dice from all dice into available
    instance->available_dice = DiceManager::dice;

    for (int i = 0; i < 16; i++) {
        instance->available_dice[i]->roll();
	}
}

void DiceManager::checkCreateInstance()
{
	if (instance == NULL) {
		instance = new DiceManager();
	}
}

Dice* DiceManager::GetRandomDie()
{
	checkCreateInstance();
    std::stringstream ss;
    ss << instance->available_dice.size() << "\n";
    
    gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, "available dice: ");
    gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, ss.str().c_str());
    
	int dice_idx = std::rand() % instance->available_dice.size();
	Dice* dice = instance->available_dice[dice_idx];
	dice->roll();
	
	//make sure this is marked as unavailable
	instance->dice_in_use.push_back(dice);
	instance->available_dice.erase(instance->available_dice.begin() + dice_idx);
    
    std::stringstream ss2;
    ss2 << "random die: " << dice->id << "\n";
    gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, ss2.str().c_str());


	return dice;
}




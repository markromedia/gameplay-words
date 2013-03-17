#include "score_controller.hpp"
#include "tile.hpp"
#include "renderable_node_repository.hpp"

ScoreController* ScoreController::instance = NULL;
std::map<std::string,int> ScoreController::letter_values_map;

void ScoreController::Init()
{
	instance = new ScoreController;
	
	instance->font = gameplay::Font::create("res/myriadpro50.gpb");
	instance->points = 0;
    instance->words = 0;

	//set up the letter values map
	
	//eights
	letter_values_map["z"] = 8; letter_values_map["q"] = 8; letter_values_map["x"] = 8; letter_values_map["j"] = 8;
	//sixes
	letter_values_map["k"] = 6; letter_values_map["v"] = 6;
	//fives
	letter_values_map["b"] = 5;
	//fours
	letter_values_map["p"] = 4; letter_values_map["y"] = 4; letter_values_map["g"] = 4; letter_values_map["f"] = 4; 
	letter_values_map["w"] = 4; letter_values_map["m"] = 4; letter_values_map["u"] = 4; letter_values_map["c"] = 4;
	//twos
	letter_values_map["l"] = 2; letter_values_map["d"] = 2; letter_values_map["r"] = 2; letter_values_map["h"] = 2;
	letter_values_map["s"] = 2; letter_values_map["n"] = 2; letter_values_map["i"] = 2;
	//ones
	letter_values_map["o"] = 1; letter_values_map["a"] = 1; letter_values_map["t"] = 1; letter_values_map["e"] = 1; 
}

void ScoreController::AddToScore( int num )
{
	instance->points += num;
    instance->words++;
}

void ScoreController::ResetScore()
{
	instance->points = 0;
    instance->words = 0;
}

void ScoreController::Update( float dt )
{

}

void ScoreController::Render()
{
	std::ostringstream oss;
	oss << instance->points;
	std::string str = oss.str();

	unsigned int width, height;
	instance->font->measureText(str.c_str(), 40, &width, &height);

	instance->font->start();
	instance->font->drawText(str.c_str(), gameplay::Game::getInstance()->getWidth() - 60 - width, 10, gameplay::Vector4(0, 0, 0, 1), 40, false);
	
    //draw word count
    std::ostringstream oss2;
    oss2 << "Word Count: " << instance->words;
    str = oss2.str();
    instance->font->measureText(str.c_str(), 30, &width, &height);
    
    instance->font->drawText(str.c_str(), gameplay::Game::getInstance()->getWidth() - 65 - width, 50, gameplay::Vector4(0, 0, 0, 1), 30, false);

    instance->font->finish();   
}

void ScoreController::AssignScoreLayer( Tile* tile )
{
	int value = letter_values_map[tile->value];
	if (value >= 1 && value <= 9) {
		std::stringstream ss;
		ss << "tile_score_" << value;
		tile->GetLayer(Tile::SCORE)->SetRenderableNode(RENDERABLE(ss.str()));
	}
}

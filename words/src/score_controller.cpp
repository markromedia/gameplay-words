#include "score_controller.hpp"

ScoreController* ScoreController::instance = NULL;

void ScoreController::Init()
{
	instance = new ScoreController;
	
	instance->font = gameplay::Font::create("res/myriadpro50.gpb");
	instance->points = 0;
    instance->words = 0;
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

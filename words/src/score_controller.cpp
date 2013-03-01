#include "score_controller.hpp"

ScoreController* ScoreController::instance = NULL;

void ScoreController::Init()
{
	instance = new ScoreController;
	
	instance->font = gameplay::Font::create("res/myriadpro50.gpb");
	instance->points = 0;
}

void ScoreController::AddToScore( int num )
{
	instance->points += num;
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
	instance->font->finish();
}

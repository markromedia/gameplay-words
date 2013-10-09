#include "timer_controller.hpp"

#include "../game.hpp"
#include "../game_state_model.hpp"


#define START_TIME (30 * 1000) - 1

TimerController* TimerController::instance = NULL;
int TimerController::font_size = 80;

void TimerController::Init()
{
	instance = new TimerController();

	instance->font = gameplay::Font::create("res/myriadpro100.gpb");

	unsigned int width;
	unsigned int height;
	instance->font->measureText(std::string("  ").c_str(), TimerController::font_size, &width, &height);
	instance->start_x = gameplay::Game::getInstance()->getWidth() / 2 - (width / 2);
}

void TimerController::Update( float dt )
{
}

void TimerController::Render()
{
	int minutes = GameStateModel::TimeRemaining()  / (60 * 1000);
	int seconds = ((int) GameStateModel::TimeRemaining() % (60 * 1000)) / 1000;

	std::ostringstream oss;
	oss << minutes << ":";
	if (seconds < 10) {
		oss << "0";
	}
	oss << seconds;

	instance->font->start();
	if (GameStateModel::TimeRemaining() < 11 * 1000) {
		instance->font->drawText(oss.str().c_str(), instance->start_x, 10, gameplay::Vector4(1, 0, 0, 1), TimerController::font_size);
	} else{
		instance->font->drawText(oss.str().c_str(), instance->start_x, 10, gameplay::Vector4(0, 0, 0, 1), TimerController::font_size);
	}
	instance->font->finish();
}





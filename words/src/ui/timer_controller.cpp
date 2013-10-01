#include "timer_controller.hpp"

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

void TimerController::Reset()
{
	instance->time_remaining = START_TIME;
	instance->timer_running = false;
	instance->total_time = 0;
}

void TimerController::StartTimer()
{
	instance->timer_running = true;
}

void TimerController::StopTimer()
{
	instance->timer_running = false;
}

void TimerController::Update( float dt )
{
	instance->total_time += dt;
	if (instance->timer_running) {
		instance->time_remaining -= dt;

		if (instance->time_remaining <= 0) {
			//times up. show the game over screen
			((words*) gameplay::Game::getInstance())->GameOver();
		} 
	}
}

void TimerController::Render()
{
	int minutes = instance->time_remaining  / (60 * 1000);
	int seconds = ((int) instance->time_remaining % (60 * 1000)) / 1000;

	std::ostringstream oss;
	oss << minutes << ":";
	if (seconds < 10) {
		oss << "0";
	}
	oss << seconds;

	instance->font->start();
	if (instance->time_remaining < 11 * 1000) {
		instance->font->drawText(oss.str().c_str(), instance->start_x, 10, gameplay::Vector4(1, 0, 0, 1), TimerController::font_size);
	} else{
		instance->font->drawText(oss.str().c_str(), instance->start_x, 10, gameplay::Vector4(0, 0, 0, 1), TimerController::font_size);
	}
	instance->font->finish();
}

void TimerController::AddTime( float millis )
{
	instance->time_remaining += millis;
}

float TimerController::TotalTimeForGame()
{
	return instance->total_time;
}





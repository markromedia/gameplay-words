#include "timer_controller.hpp"

TimerController* TimerController::instance = NULL;

#define START_TIME (121 * 1000) - 1

void TimerController::Init()
{
	instance = new TimerController();

	instance->font = gameplay::Font::create("res/myriadpro50.gpb");
}

void TimerController::Reset()
{
	instance->time_remaining = START_TIME;
	instance->timer_running = false;
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
		instance->font->drawText(oss.str().c_str(), 60, 10, gameplay::Vector4(1, 0, 0, 1), 40);
	} else{
		instance->font->drawText(oss.str().c_str(), 60, 10, gameplay::Vector4(0, 0, 0, 1), 40);
	}
	instance->font->finish();
}



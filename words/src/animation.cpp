#include "animation.hpp"

void words::Animation::reset()
{
	this->total_running_time = 0;
	this->step_index = 0;
	this->running = false;
	for (unsigned int i = 0; i < steps.size(); i++) {
		steps[i].running_time = 0;
	}
}

void words::Animation::Add(float duration, void (*StepFunc)(words::Animation*, float) )
{
	Step step;
	step.duration = duration;
	step.func = StepFunc;
	this->steps.push_back(step);
}

bool words::Animation::Next()
{
	step_index++;
	return step_index < steps.size();
}

void words::Animation::Start()
{
	this->running = true;
}

void words::Animation::Stop()
{
	this->running = false;
}

void words::Animation::Update( float dt )
{
	if (!running) {
		return;
	}

	this->total_running_time += dt;

	if (step_index < steps.size()) {
		Step current_step = this->steps[step_index];
		current_step.func(this, dt);
		current_step.running_time += dt;
		//check to see if we're done with step, then try to advance
		if (current_step.running_time >= current_step.duration) {
			if (!this->Next()) //advance to next step if we can, otherwise stop the animation
				this->Stop();
		}
	}
}

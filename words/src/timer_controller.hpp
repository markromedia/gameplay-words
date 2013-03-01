#ifndef __TIMER_CONTROLLER__hpp
#define __TIMER_CONTROLLER__hpp

#include <sstream>

#include "gameplay.h"

class TimerController {
private:
	/// @summary	The used to draw the text itself.
	gameplay::Font* font;

	/// @summary	The time remaining.
	float time_remaining;

	/// @summary	whether or not the timer is running.
	bool timer_running;

	/// @summary	The instance.
	static TimerController* instance;
public:
	/// Resets the clock
	static void Reset();

	/// Starts the timer.
	static void StartTimer();

	/// Stops the timer.
	static void StopTimer();
	
	/// Initialises this object.
	static void Init();

	/// Updates this object
	/// @param	dt	The dt.
	static void Update(float dt);

	/// Renders this object.
	static void Render();
};

#endif  // __TIMER_CONTROLLER__hpp
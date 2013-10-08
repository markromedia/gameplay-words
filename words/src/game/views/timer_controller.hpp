#ifndef __TIMER_CONTROLLER__hpp
#define __TIMER_CONTROLLER__hpp

#include <sstream>

#include "gameplay.h"
#include "../../words.h"

class TimerController {
private:
	/// @summary	The used to draw the text itself.
	gameplay::Font* font;

	/// @summary	The time remaining.
	float time_remaining;

	/// @summary	The total time for this game
	float total_time;

	/// @summary	whether or not the timer is running.
	bool timer_running;

	/// @summary	The instance.
	static TimerController* instance;

	/// @summary	Size of the font.
	static int font_size;

	/// @summary	The start x coordinate.
	int start_x;
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

	/// Adds a time to the counter
	/// @param	millis	The millis.
	static void AddTime(float millis);

	/// Gets the total time for game.
	/// @return	The total number of time for game.
	static float TotalTimeForGame(); 
};

#endif  // __TIMER_CONTROLLER__hpp
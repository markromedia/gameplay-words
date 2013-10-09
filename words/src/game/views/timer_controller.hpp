#ifndef __TIMER_CONTROLLER__hpp
#define __TIMER_CONTROLLER__hpp

#include <sstream>

#include "gameplay.h"
#include "../../words.h"

class TimerController {
private:
	/// @summary	The used to draw the text itself.
	gameplay::Font* font;

	/// @summary	The instance.
	static TimerController* instance;

	/// @summary	Size of the font.
	static int font_size;

	/// @summary	The start x coordinate.
	int start_x;
public:
	/// Initialises this object.
	static void Init();

	/// Updates this object
	/// @param	dt	The dt.
	static void Update(float dt);

	/// Renders this object.
	static void Render();
};

#endif  // __TIMER_CONTROLLER__hpp
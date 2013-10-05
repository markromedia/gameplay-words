#ifndef __INPUT_EVENT_HANDLER__hpp
#define __INPUT_EVENT_HANDLER__hpp

#include <map>

#include "gameplay.h"
#include "words.h"

/// Values that represent TouchState.
enum TouchState { TOUCH_DOWN, TOUCH_UP };

class InputEventHandler {
private:
	/// Makes sure we have an instance ready.
	static void _checkCreateInstance();

	/// @summary	The instance.
	static InputEventHandler* instance;

	/// Handles the touch event.
	/// @param	game		instance of the game itself
	/// @param	x	The x coordinate.
	/// @param	y	The y coordinate.
	/// @return	true if it succeeds, false if it fails.
	bool handleTouchEvent(words* game, int x, int y);

	/// @summary	State of the touch.
	TouchState touchState;

	/// @summary	true to enable, false to disable.
	bool enabled;
public:
	/// Gets returns singleton instance
	/// @return	null if it fails, else.
	static InputEventHandler* get();

	/// Sets the input handler to enabled or not
	/// @param	enabled	true to enable, false to disable.
	void SetEnabled(bool enabled);

	/// Touch event handler.
	/// @param	game		instance of the game itself
	/// @param	evt				The event.
	/// @param	x				The x coordinate.
	/// @param	y				The y coordinate.
	/// @param	contactIndex	Zero-based index of the contact.
	void touchEvent(words* game, gameplay::Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);

	/// Mouse event the mouse event listener
	/// @param	game		instance of the game itself
	/// @param	evt		  	The event.
	/// @param	x		  	The x coordinate.
	/// @param	y		  	The y coordinate.
	/// @param	wheelDelta	The wheel delta.
	/// @return	true if it succeeds, false if it fails.
	bool mouseEvent(words* game, gameplay::Mouse::MouseEvent evt, int x, int y, int wheelDelta);

	/// The key event handler.
	/// @param	game		instance of the game itself
	/// @param	evt	The event.
	/// @param	key	The key.
	void keyEvent(words* game, gameplay::Keyboard::KeyEvent evt, int key);
};


#endif  // __INPUT_EVENT_HANDLER__hpp
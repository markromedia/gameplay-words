#ifndef __SCORE_CONTROLLER__hpp
#define __SCORE_CONTROLLER__hpp

#include <algorithm>

#include "gameplay.h"

class ScoreController {
private:
	/// @summary	The used to draw the text itself.
	gameplay::Font* font;

	/// @summary	The instance.
	static ScoreController* instance;

	/// @summary	The current displayed points.
	int points;
public:
	/// Initialises this object.
	static void Init();

	/// Updates this object
	/// @param	dt	The dt.
	static void Update(float dt);

	/// Renders this object.
	static void Render();

	/// Adds to the score.
	/// @param	num	Number of.
	static void AddToScore(int num);
};

#endif  // __SCORE_CONTROLLER__hpp
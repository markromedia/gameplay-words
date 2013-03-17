#ifndef __SCORE_CONTROLLER__hpp
#define __SCORE_CONTROLLER__hpp

#include <algorithm>
#include <set>
#include <sstream>

#include "gameplay.h"

class Tile;

class ScoreController {
private:
	/// @summary	The used to draw the text itself.
	gameplay::Font* font;

	/// @summary	The instance.
	static ScoreController* instance;

	/// @summary	The current displayed points.
	int points;
    
    /// @summary	The number of words
    int words;

	/// @summary	The letter values map.
	static std::map<std::string,int> letter_values_map;
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

	/// Resets the score.
	static void ResetScore();

	/// Assign score layer to the tile
	/// @param [in,out]	tile	If non-null, the tile.
	static void AssignScoreLayer(Tile* tile);
};

#endif  // __SCORE_CONTROLLER__hpp
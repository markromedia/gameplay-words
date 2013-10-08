#ifndef __SCORE_CONTROLLER__hpp
#define __SCORE_CONTROLLER__hpp

#include <algorithm>
#include <set>
#include <sstream>

#include "gameplay.h"


class Tile;

class ScoreView {
private:
	enum PointsAnimation { NONE, POPPING, SHRINKING, STEADY, FADING };

	/// @summary	The used to draw the text itself.
	gameplay::Font* font;

	/// @summary	The instance.
	static ScoreView* instance;

	/// @summary	The current displayed points.
	int game_points;
    
    /// @summary	The number of words
    int words;

	/// @summary	The letter values map.
	static std::map<std::string,int> letter_point_values_map;

	/// @summary	The time levels.
	static float time_levels[6];

	/// @summary	The points text coords
	static float points_text_coords[11][4];

	/// @summary	The points animation step.
	PointsAnimation points_animation_step;

	/// Draw the character at the index at the location provided
	/// by current_characters_screen_location. will increment x value
	/// when done
	/// @param	char_index	Zero-based index of the character.
	void drawPointCharacter(int char_index);

	/// @summary	The points batch.
	gameplay::SpriteBatch* points_batch;

	/// @summary	The current characters screen location
	gameplay::Vector2 initial_characters_screen_location;

	/// @summary	The current characters screen location
	gameplay::Vector2 current_characters_screen_location;

	/// @summary	The points to add
	int points_for_word;

	/// @summary	How lnong the current animation step has been running for
	int animation_step_runtime;

	/// @summary	The points scale.
	float points_scale;

	/// @summary	The points alpha.
	float points_alpha;

	bool draw_points;
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
	static void AddToScore(std::vector<Tile*> selected_tiles, gameplay::Vector2* last_known_touch);

	/// Resets the score.
	static void ResetScore();

	/// Gets the round points.
	/// @return	.
	static int RoundPoints();

	/// Assign score layer to the tile
	/// @param [in,out]	tile	If non-null, the tile.
	static void AssignScoreLayer(Tile* tile);

	/// Gets the words for round.
	/// @return	.
	static int WordsForRound();
};

#endif  // __SCORE_CONTROLLER__hpp
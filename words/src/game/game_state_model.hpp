#ifndef __GAME_STATE_MODEL_hpp
#define __GAME_STATE_MODEL_hpp

#include <vector>

#include "gameplay.h"

class GameStateModel {
private:

	/// @summary	The instance.
	static GameStateModel* instance;

	/// @summary	The number of points earned so far for this game
	int game_points;

	/// @summary	Number of words found 
	int word_count;

	/// @summary	The time remaining.
	float time_remaining;

	/// @summary	The total time for this game
	float total_time;
public:

	/// Resets the game state
	static void Reset();

	/// Gets the game points.
	/// @return	game points 
	static int GamePoints();

	/// Gets the word count.
	/// @return	.
	static int WordCount();

	/// Gets the time remaining.
	/// @return	.
	static float TimeRemaining();

	/// Gets the total time.
	/// @return	The total number of time.
	static float TotalTime();

	/// Adds a time to the counter
	/// @param	millis	The millis.
	static void AddTime(float millis);

	/// Updates the given dt.
	/// @param	dt	The dt.
	static void Update(float dt);
};


#endif  // __GAME_STATE_MODEL_hpp
#ifndef __GAME_STATE_MODEL_hpp
#define __GAME_STATE_MODEL_hpp

#include <vector>

#include "gameplay.h"

class TimeTankModel;

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

	/// @summary	The time tank models.
	std::vector<TimeTankModel*> all_time_tank_models;

	/// @summary	The active time tank modes.
	std::vector<TimeTankModel*> active_time_tank_models;

	/// Default constructor.
	GameStateModel();
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

	/// Adds a word points.
	/// @param	points	The points.
	static void AddWordPoints(int points);

	/// Updates the given dt.
	/// @param	dt	The dt.
	static void Update(float dt);

	/// Gets the maximum time tank charge.
	/// @return	.
	static int MaxTimeTankCharge();

	/// Gets the maximum number of time tanks.
	/// @return	.
	static int MaxNumberOfTimeTanks();

	/// Gets the time tanks.
	/// @return	null if it fails, else.
	static std::vector<TimeTankModel*> TimeTanks();
};

class TimeTankModel {
private:

	/// @summary	The current charge of the tank.
	int current_charge;

	/// @summary	true if charged.
	bool charged;
public:

	/// Gets the current charge.
	/// @return	.
	int CurrentCharge();

	/// Query if this object is charged.
	/// @return	true if charged, false if not.
	bool IsCharged();

	/// Adds a charge. If fully charges this, returns remainder
	/// @param	amt	The amt.
	/// @return	.
	int AddCharge(int amt);
};


#endif  // __GAME_STATE_MODEL_hpp
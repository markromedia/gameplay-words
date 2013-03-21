#ifndef __STATISTICS__hpp
#define __STATISTICS__hpp

#include <string>
#include <sstream>
#include <queue>
#include "rest_handler.hpp"


class RoundData {
public:
	/// @summary	space delimited words for round.
	std::stringstream* words_for_round; 

	/// @summary	space delimited points for round.
	std::stringstream* points_for_round; 
};

class Statistics {
private:
	/// @summary	The instance.
	static Statistics* instance;

	/// @summary	Information describing the current round.
	RoundData* current_round_data;

	/// @summary	Information describing the queued round.
	std::queue<RoundData*> queued_round_data;
public:
	/// Initialises this object.
	static void Init();

	/// Starts a new round.
	static void StartNewRound();

	/// Adds a word to round with its points
	/// @param	word  	The word.
	/// @param	points	The points.
	static void AddWordToRound(std::string word, int points);

	/// Round complete.
	/// @param	round_points	The round points.
	static void RoundComplete(int round_points);
};

#endif  // __STATISTICS__hpp
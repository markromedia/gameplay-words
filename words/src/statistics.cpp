#include "statistics.hpp"
#include "words.h"

Statistics* Statistics::instance = NULL;

void Statistics::Init()
{
	instance = new Statistics;
}

void Statistics::StartNewRound()
{
	instance->current_round_data = new RoundData;
	instance->current_round_data->words_for_round = new std::stringstream;
	instance->current_round_data->points_for_round = new std::stringstream;
	instance->queued_round_data.push(instance->current_round_data);
}

void Statistics::AddWordToRound( std::string word, int points )
{
	RoundData* round = instance->current_round_data;
	*round->words_for_round << word << " ";
	*round->points_for_round << points << " ";
}

void Statistics::RoundComplete( int round_points )
{
	//if (RestHandler::get()->HasInternetConnection()) {
	//	while (!instance->queued_round_data.empty()) {
	//		RoundData* round = instance->queued_round_data.front();
	//		instance->queued_round_data.pop();

	//		RoundLog roundLog;
	//		roundLog.score = round_points;
	//		roundLog.points = round->points_for_round->str();
	//		roundLog.words = round->words_for_round->str();
	//		roundLog.version = APP_VERSION;

	//		////RestHandler::get()->SubmitRoundLog(&roundLog);

	//		delete round;
	//	}
	//} 
}

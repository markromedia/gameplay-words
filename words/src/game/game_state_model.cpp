#include "game_state_model.hpp"

GameStateModel* GameStateModel::instance;

#define START_TIME (30 * 1000) - 1

void GameStateModel::Reset()
{
	if (GameStateModel::instance == NULL)
		GameStateModel::instance = new GameStateModel();

	GameStateModel::instance->game_points = 0;
	GameStateModel::instance->word_count = 0;
	GameStateModel::instance->time_remaining = START_TIME;
	GameStateModel::instance->total_time = 0;

}

void GameStateModel::Update( float dt )
{
	instance->total_time += dt;
	instance->time_remaining -= dt;
}

void GameStateModel::AddTime( float millis )
{
	instance->time_remaining += millis;
	instance->word_count += millis; //TODO move this
}

int GameStateModel::GamePoints()
{
	return instance->game_points;
}

int GameStateModel::WordCount()
{
	return instance->word_count;
}

float GameStateModel::TimeRemaining()
{
	return instance->time_remaining;
}

float GameStateModel::TotalTime()
{
	return instance->total_time;
}





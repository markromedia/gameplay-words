#include "game_state_model.hpp"

GameStateModel* GameStateModel::instance;

static const float START_TIME = (30 * 1000) - 1;
static const int MAX_TIME_TANKS = 5;
static const int TIME_TANK_COUNT = 5;
static const int TIME_TANK_MAX_CHARGE = 100;

///-----------------------------------------------------------------------------------------------

GameStateModel::GameStateModel()
{
	for (int i = 0; i < MAX_TIME_TANKS; i++) {
		this->all_time_tank_models.push_back(new TimeTankModel());
	}

	for (int i = 0; i < TIME_TANK_COUNT; i++) {
		this->active_time_tank_models.push_back(this->all_time_tank_models[i]);
	}
}

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
	instance->word_count++; //TODO move this
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

void GameStateModel::AddWordPoints( int points )
{
	int remainder = 0;
	for (int i = 0; i < TIME_TANK_COUNT; i++) {
		TimeTankModel* current_tank = GameStateModel::instance->active_time_tank_models[i];
		if (!current_tank->IsCharged()) {
			remainder = current_tank->AddCharge(points + remainder);
			if (remainder == 0) {
				goto remainder_is_zero;
			}
		}
	}

	remainder_is_zero:;
}

std::vector<TimeTankModel*> GameStateModel::TimeTanks()
{
	return instance->active_time_tank_models;
}

int GameStateModel::MaxTimeTankCharge()
{
	return TIME_TANK_MAX_CHARGE;
}

int GameStateModel::MaxNumberOfTimeTanks()
{
	return MAX_TIME_TANKS;
}

///-----------------------------------------------------------------------------------------------

int TimeTankModel::CurrentCharge()
{
	return current_charge;
}

bool TimeTankModel::IsCharged()
{
	return charged;
}

int TimeTankModel::AddCharge( int amt )
{
	if (!charged) {
		this->current_charge += amt;
		if (this->current_charge >= TIME_TANK_MAX_CHARGE) {
			this->charged = true;
			return TIME_TANK_MAX_CHARGE - this->current_charge;
		}
	}

	return 0;
}

///-----------------------------------------------------------------------------------------------
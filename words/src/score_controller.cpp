#include "score_controller.hpp"
#include "tile.hpp"
#include "renderable_node_repository.hpp"
#include "statistics.hpp"

//singleton instance
ScoreController* ScoreController::instance = NULL;
//map of points of a letter to the the letter itself
std::map<std::string,int> ScoreController::letter_point_values_map;
//points texture coords
//(width/height/crop-x/crop-y)
float ScoreController::points_text_coords[11][4] = {
	{52, 64, 42, 64}, //0
	{36, 64, 94, 64}, //1
	{49, 64, 130, 64}, //2
	{48, 64, 179, 64}, //3
	{52, 64, 227, 64}, //4
	{48, 64, 279, 64}, //5
	{52, 64, 327, 64}, //6
	{48, 64, 379, 64}, //7
	{51, 64, 427, 64}, //8
	{51, 64, 427, 0}, //9
	{42, 64, 0, 64} //plus
};

void ScoreController::Init()
{
	instance = new ScoreController;
	
	instance->points_batch = gameplay::SpriteBatch::create("res/png/points_font.png");
	instance->font = gameplay::Font::create("res/myriadpro50.gpb");
	ResetScore();

	//set up the letter values map
	
	//eights
	letter_point_values_map["z"] = 8; letter_point_values_map["q"] = 8; letter_point_values_map["x"] = 8; letter_point_values_map["j"] = 8;
	//sixes
	letter_point_values_map["k"] = 6; letter_point_values_map["v"] = 6;
	//fives
	letter_point_values_map["b"] = 5;
	//fours
	letter_point_values_map["p"] = 4; letter_point_values_map["y"] = 4; letter_point_values_map["g"] = 4; letter_point_values_map["f"] = 4; 
	letter_point_values_map["w"] = 4; letter_point_values_map["m"] = 4; letter_point_values_map["u"] = 4; letter_point_values_map["c"] = 4;
	//twos
	letter_point_values_map["l"] = 2; letter_point_values_map["d"] = 2; letter_point_values_map["r"] = 2; letter_point_values_map["h"] = 2;
	letter_point_values_map["s"] = 2; letter_point_values_map["n"] = 2; letter_point_values_map["i"] = 2;
	//ones
	letter_point_values_map["o"] = 1; letter_point_values_map["a"] = 1; letter_point_values_map["t"] = 1; letter_point_values_map["e"] = 1; 
}

void ScoreController::AddToScore( std::vector<Tile*> selected_tiles, gameplay::Vector2* last_known_touch )
{
	instance->points_animation_step = POPPING;
	instance->animation_step_runtime = 0;
	instance->points_scale = 1.0f;
	instance->points_alpha = 1.0f;
	instance->initial_characters_screen_location.x = last_known_touch->x;
	instance->initial_characters_screen_location.y = last_known_touch->y - 64;
	instance->current_characters_screen_location.x = last_known_touch->x;
	instance->current_characters_screen_location.y = last_known_touch->y - 64;

	//figure out the score to add 
	instance->points_for_word = 0;
	std::stringstream ss;
	for(std::vector<Tile*>::iterator it = selected_tiles.begin(); it != selected_tiles.end(); ++it) {			
		Tile* t = (*it);
		instance->points_for_word += letter_point_values_map[t->value];
		ss << t->value;
	}
	instance->points_for_word += (selected_tiles.size() * 2);

	//add to the statistics
	Statistics::AddWordToRound(ss.str(), instance->points_for_word);
	
	//increment word count
	instance->words++;
	instance->game_points += instance->points_for_word;
}

void ScoreController::ResetScore()
{
	instance->game_points = 0;
	instance->words = 0;
	instance->animation_step_runtime = 0;
	instance->points_for_word = 0;
	instance->points_animation_step = NONE;
	instance->points_scale = 1.0f;
	instance->points_alpha = 1.0f;
}

void ScoreController::Update( float dt )
{
	switch (instance->points_animation_step) {
	case POPPING:
		gameplay::MathUtil::smooth(&instance->points_scale, 1.3f, dt, 64);
		if (instance->points_scale >= 1.29f) {
			instance->points_scale = 1.3f;
			instance->points_animation_step = SHRINKING;
		}
		break;
	case SHRINKING: 
		gameplay::MathUtil::smooth(&instance->points_scale, 1.0f, dt, 64);
		gameplay::MathUtil::smooth(&instance->points_alpha, 0.0f, dt, 64);
		if (instance->points_scale <= 1.05f) {
			instance->points_scale = 1.0f;
			instance->points_animation_step = NONE;
		}
		break;
	case FADING: 
		gameplay::MathUtil::smooth(&instance->points_alpha, 0.3f, dt, 64);
		if (instance->points_alpha <= 0.31f) {
			instance->points_alpha = 0.3f;
			instance->points_animation_step = NONE;
		}
		break;
	}
}

void ScoreController::Render()
{
	std::ostringstream oss;
	oss << instance->game_points;
	std::string str = oss.str();

	unsigned int width, height;
	instance->font->measureText(str.c_str(), 40, &width, &height);

	instance->font->start();
	instance->font->drawText(str.c_str(), gameplay::Game::getInstance()->getWidth() - 60 - width, 10, gameplay::Vector4(0, 0, 0, 1), 40, false);
	
    //draw word count
    std::ostringstream oss2;
    oss2 << "Word Count: " << instance->words;
    str = oss2.str();
    instance->font->measureText(str.c_str(), 30, &width, &height);
    
    instance->font->drawText(str.c_str(), gameplay::Game::getInstance()->getWidth() - 65 - width, 50, gameplay::Vector4(0, 0, 0, 1), 30, false);

    instance->font->finish();   

	if (instance->points_animation_step != NONE) {
		instance->points_batch->start();
		//draw the plus sign
		instance->drawPointCharacter(10);

		//draw each character now
		if (instance->points_for_word > 100) {
			int h = instance->points_for_word / 100;
			instance->drawPointCharacter(h);
		}

		if (instance->points_for_word > 10) {
			int t = instance->points_for_word / 10;
			instance->drawPointCharacter(t);
		}

		instance->drawPointCharacter(instance->points_for_word % 10);
		
		instance->points_batch->finish();

		//reset location
		instance->current_characters_screen_location.x = instance->initial_characters_screen_location.x;
		instance->current_characters_screen_location.y = instance->initial_characters_screen_location.y;
	}
}

void ScoreController::drawPointCharacter( int p_idx )
{
	float p_width = points_text_coords[p_idx][0];
	float p_height = points_text_coords[p_idx][1];
	float u1 = points_text_coords[p_idx][2] / 512.0f;
	float v1 = points_text_coords[p_idx][3] / 128.0f;
	float u2 = (points_text_coords[p_idx][2] + p_width) / 512.0f;
	float v2 = (points_text_coords[p_idx][3] + p_height) / 128.0f;

	points_batch->draw(current_characters_screen_location.x, current_characters_screen_location.y, 0.0f, 
		p_width * points_scale, p_height * points_scale, 
		u1, v2, u2, v1, 
		gameplay::Vector4(1, 1, 1, points_alpha), true);
	//move x
	current_characters_screen_location.x = current_characters_screen_location.x + (points_scale * p_width) + 1;
}

void ScoreController::AssignScoreLayer( Tile* tile )
{
	int value = letter_point_values_map[tile->value];
	if (value >= 1 && value <= 9) {
		std::stringstream ss;
		ss << "tile_score_" << value;
		tile->GetLayer(Tile::SCORE)->SetRenderableNode(RENDERABLE(ss.str()));
	}
}

int ScoreController::RoundPoints()
{
	return instance->game_points;
}




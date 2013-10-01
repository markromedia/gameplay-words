#include "menu.hpp"
#include "../input_event_handler.hpp"
#include "score_controller.hpp"

//(width/height/crop-x/crop-y)
float Menu::menu_items_coords[7][4] = {
	{505, 82, 0, 0}, //game over
	{260, 81, 0, 89}, //menu
	{340, 85, 0, 175}, //new game button
	{340, 85, 0, 275}, //replay button
	{340, 85, 0, 375}, //resume button
	{313, 52, 0, 460}, //word count text
	{136, 48, 340, 456} //score text
};

float Menu::menu_numbers_coords[10][4] = {
	{35, 46, 0, 82}, //0
	{24, 46, 46, 82}, //1
	{34, 46, 86, 82}, //2
	{34, 46, 129, 82}, //3
	{37, 46, 171, 82}, //4
	
	{34, 46, 5, 11}, //5
	{36, 46, 48, 11}, //6
	{34, 46, 92, 11}, //7
	{35, 46, 134, 11}, //8
	{36, 46, 177, 11} //9
};

Menu::Menu()
{
	menu_items = gameplay::SpriteBatch::create("res/png/menu_items.png");
	menu_numbers = gameplay::SpriteBatch::create("res/png/menu_items_numbers.png");
	this->visible = false;
	//this->initializeRocket();
}

void Menu::Hide()
{
	visible = false;
	TimerController::StartTimer();
}

void Menu::Show(bool game_over_screen)
{
	visible = true;
	is_game_over = game_over_screen;
	TimerController::StopTimer();
}

void Menu::Render()
{
	if (!visible) {
		return;
	}

	//draw background
	menu_items->start();

	int center_x = gameplay::Game::getInstance()->getWidth() / 2;
	int start_y = 100;
	int text_start = center_x - 220;

	//draw top logo
	if (is_game_over) {
		drawItem(0, center_x - menu_items_coords[0][0] / 2, start_y);
		start_y += menu_items_coords[0][1] + 100;
	} else {
		drawItem(1, center_x - menu_items_coords[1][0] / 2, start_y);
		start_y += menu_items_coords[1][1] + 100;
	}

	//draw text
	menu_numbers->start();
	drawItem(6, text_start, start_y); //time label
	drawNumber(TimerController::TotalTimeForGame() / 1000, text_start + menu_items_coords[6][0] + 10, start_y); //score text
	start_y += menu_items_coords[6][1] + 20;

	drawItem(5, text_start, start_y); //word count label
	drawNumber(ScoreController::WordsForRound(), text_start + menu_items_coords[5][0] + 10, start_y); //word count text
	start_y += menu_items_coords[5][1] + 150;
	menu_numbers->finish();

	//draw the new game button
	button_positions[0][0] = center_x -  menu_items_coords[2][0] / 2;
	button_positions[0][1] = start_y;
	drawItem(2, center_x -  menu_items_coords[2][0] / 2, start_y); start_y += menu_items_coords[2][1] + 50;
	
	//draw resume or replay
	button_positions[1][1] = start_y;
	if (is_game_over) {
		button_positions[1][0] = center_x -  menu_items_coords[3][0] / 2;
		drawItem(3, center_x -  menu_items_coords[3][0] / 2, start_y); 
	} else {
		button_positions[1][0] = center_x -  menu_items_coords[4][0] / 2;
		drawItem(4, center_x -  menu_items_coords[4][0] / 2, start_y); 
	}

	menu_items->finish();

	//_rocketContext->Render();
}

void Menu::drawNumber( int number, int x, int y )
{
	std::stringstream ss;
	ss << number;
	std::string s = ss.str();
	for (int i = 0; i < s.length(); i++) {
		int p_idx = s.at(i) - 48;

		float p_width = menu_numbers_coords[p_idx][0];
		float p_height = menu_numbers_coords[p_idx][1];
		//hack to get around the text coords being in screen space coords
		float t_y = menu_items_coords[p_idx][3];

		float u1 = menu_numbers_coords[p_idx][2] / 256.0f;
		float v1 = menu_numbers_coords[p_idx][3] / 128.0f;
		float u2 = (menu_numbers_coords[p_idx][2] + p_width) / 256.0f;
		float v2 = (menu_numbers_coords[p_idx][3] + p_height) / 128.0f;

		menu_numbers->draw(x, y, 0.0f, 
			p_width, p_height, 
			u1, v2, u2, v1, 
			gameplay::Vector4::one(), false);
		//move x
		x += p_width + 2;
	}
}

void Menu::drawItem( int p_idx, int x, int y )
{

	float p_width = menu_items_coords[p_idx][0];
	float p_height = menu_items_coords[p_idx][1];
	//hack to get around the text coords being in screen space coords
	float t_y = 512 - menu_items_coords[p_idx][3] - p_height;

	float u1 = menu_items_coords[p_idx][2] / 512.0f;
	float v1 = t_y / 512.0f;
	float u2 = (menu_items_coords[p_idx][2] + p_width) / 512.0f;
	float v2 = (t_y + p_height) / 512.0f;

	menu_items->draw(x, y, 0.0f, 
		p_width, p_height, 
		u1, v2, u2, v1, 
		gameplay::Vector4::one(), false);
}

bool Menu::IsVisible()
{
	return this->visible;
}

void Menu::Update( float dt )
{
	//_rocketContext->Update();
}

bool Menu::HandleTouchDownEvent( gameplay::Ray& ray, int x, int y )
{
	if (!visible) {
		return false;
	}
	for (int i = 0 ; i < 2; i++) {
		bool is_collision = 
			x >= button_positions[i][0] && x <= button_positions[i][0] + 340 &&
			y >= button_positions[i][1] && y <= button_positions[i][1] + 85;

		if (is_collision) {
			if (i == 0) {
				((words*) gameplay::Game::getInstance())->NewGame();
				this->Hide();
				//new game
			} else if (is_game_over) {
				this->Hide();
				//replay
			} else {
				this->Hide();
				//resume
			}
		}
	}

	return true;
}

void Menu::initializeRocket()
{
	//Rocket::Core::SetFileInterface(&_fileInterface);
	//Rocket::Core::SetRenderInterface(&_renderInterface);
	//Rocket::Core::SetSystemInterface(&_systemInterface);

	//Rocket::Core::Initialise();
	//_rocketContext = Rocket::Core::CreateContext("main",
	//	Rocket::Core::Vector2i(gameplay::Game::getInstance()->getWidth(), gameplay::Game::getInstance()->getHeight()));

	//Rocket::Core::String font_names[4];
	//font_names[0] = "Delicious-Roman.otf";
	//font_names[1] = "Delicious-Italic.otf";
	//font_names[2] = "Delicious-Bold.otf";
	//font_names[3] = "Delicious-BoldItalic.otf";

	//for (int i = 0; i < sizeof(font_names) / sizeof(Rocket::Core::String); i++)
	//{
	//	Rocket::Core::FontDatabase::LoadFontFace(font_names[i]);
	//}

	//Rocket::Core::ElementDocument* document = _rocketContext->LoadDocument("test.rml");
	//document->Show();
	//document->RemoveReference();
}

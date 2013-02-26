#include "selected_text_label.hpp"

void SelectedTextLabel::Init()
{
	this->font = gameplay::Font::create("res/myriadpro50.gpb");
	this->font_size = 50;

	this->left_bg = gameplay::SpriteBatch::create("res/png/selected_text_left_bg.png");
	this->right_bg = gameplay::SpriteBatch::create("res/png/selected_text_right_bg.png");
	this->tiling_bg = gameplay::SpriteBatch::create("res/png/selected_text_tiling_bg.png");

	//make sure the tiling one actually tiles
	this->tiling_bg->getSampler()->setWrapMode(gameplay::Texture::REPEAT, gameplay::Texture::CLAMP);
	int a = 1;
}

void SelectedTextLabel::SetStringToDraw( std::string str )
{
	//reset visible time to start over 
	total_visible_time = 0;
	this->string_to_draw = str;
	toUpper(this->string_to_draw);
}

void SelectedTextLabel::Render()
{
	if (!do_render || string_to_draw.length() == 0) {
		return;
	}

	font->start();
	//grab the width and height of the text
	unsigned int width;
	unsigned int height;
	font->measureText(string_to_draw.c_str(), font_size, &width, &height);

	//basic position vars
	int left_x_pos = gameplay::Game::getInstance()->getWidth() / 2 - (width / 2);
	int right_x_pos = gameplay::Game::getInstance()->getWidth() / 2 + (width / 2);
	int y_pos = 100;

	int bg_left = 287;
	int bg_right = 318;
	int bg_ypos = y_pos - 6;

	//draw the background stuff
	//if drawing more than 1 character, move starts and put tiling
	if (string_to_draw.length() != 1) {
		bg_left -= 12 * string_to_draw.length();
		bg_right += 12 * string_to_draw.length();

		tiling_bg->start();
		tiling_bg->draw(bg_left + 31, bg_ypos, 0.0f, bg_right - bg_left - 31, 64, 0.0f, 1.0f, 1.0f, 0.0f, gameplay::Vector4::one(), false);
		tiling_bg->finish();
	} 

	left_bg->start();
	left_bg->draw(bg_left, bg_ypos, 0.0f, 32, 64, 0.0f, 1.0f, 1.0f, 0.0f, gameplay::Vector4::one(), false);
	left_bg->finish();

	right_bg->start();
	right_bg->draw(bg_right, bg_ypos, 0.0f, 32, 64, 0.0f, 1.0f, 1.0f, 0.0f, gameplay::Vector4::one(), false);
	right_bg->finish();

	font->drawText(string_to_draw.c_str(), left_x_pos, y_pos, gameplay::Vector4(0, 0, 0, 1), font_size);
	font->finish();
}

void SelectedTextLabel::toUpper( std::string& str )
{
	for(unsigned int l = 0; l < str.length(); l++)
	{
		str[l] = std::toupper(str[l]);
	}
}

void SelectedTextLabel::Update( float dt )
{
	do_render = total_visible_time <= 500;
	total_visible_time += dt;
}

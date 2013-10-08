#include "menu_icon_controller.hpp"

#include "../../words.h"
#include "../../ext/scene_manager.hpp"

MenuIconController* MenuIconController::instance = NULL;

MenuIconController::MenuIconController()
{
	this->menu_icon = gameplay::SpriteBatch::create("res/png/settings_icon.png");
	this->visible = true;
	
	int screen_width = gameplay::Game::getInstance()->getWidth();
	int screen_height = gameplay::Game::getInstance()->getHeight();
	float scale = 1.5;
	int size = 64;
	
	icon_height = size * scale;
	icon_width = size * scale;
	x_pos = screen_width - size * scale;
	y_pos = 0;

	src_rect = gameplay::Rectangle(0, 0, size, size);
	dest_rect = gameplay::Rectangle(x_pos, y_pos, icon_width, icon_height);
}

void MenuIconController::Init()
{
	MenuIconController::instance = new MenuIconController();
}

void MenuIconController::SetVisibility(bool visible) 
{
	instance->visible = visible;
}

bool MenuIconController::IsVisible() 
{
	return instance->visible;
}


void MenuIconController::Render()
{
	if (!instance->visible) {
		return;
	}

	instance->menu_icon->start();
	instance->menu_icon->draw(instance->dest_rect, instance->src_rect);
	instance->menu_icon->finish();
}

bool MenuIconController::HandleTouchDownEvent(gameplay::Ray& ray, int x, int y)
{
	if (!instance->visible) {
		return false;
	}

	bool is_collision = 
		x >= instance->x_pos && x <= instance->x_pos + instance->icon_width &&
		y >= instance->y_pos && y <= instance->y_pos + instance->icon_height;

	if (is_collision) {
		SceneManager::get()->GotoMenuScene(false);
		return true;
	}

	return false;
}


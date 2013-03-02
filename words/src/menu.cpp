#include "menu.hpp"
#include "input_event_handler.hpp"

Menu::Menu()
{
	//init form stuff
	form = Form::create("res/menu.form");

	container = (gameplay::Container*)form->getControl("presets");
	new_game_button = (gameplay::Button*)form->getControl("new_game");
	new_game_button->addListener(this, Listener::PRESS);

	background = gameplay::SpriteBatch::create("res/png/overlay.png");
	background->getSampler()->setWrapMode(gameplay::Texture::REPEAT, gameplay::Texture::REPEAT);

	form->setConsumeInputEvents(false);
	container->setConsumeInputEvents(false);
	new_game_button->setConsumeInputEvents(false);
	this->visible = false;
}

void Menu::Hide()
{
	visible = false;
	InputEventHandler::get()->SetEnabled(true);
	TimerController::StartTimer();
	form->setConsumeInputEvents(false);
	container->setConsumeInputEvents(false);
	new_game_button->setConsumeInputEvents(false);
}

void Menu::Show()
{
	visible = true;
	InputEventHandler::get()->SetEnabled(false);
	TimerController::StopTimer();
	form->setConsumeInputEvents(true);
	container->setConsumeInputEvents(true);
	new_game_button->setConsumeInputEvents(true);
}

void Menu::Render()
{
	if (!visible) {
		return;
	}

	//draw background
	background->start();
	background->draw(0, 0, 0.0f, 
					gameplay::Game::getInstance()->getWidth(), gameplay::Game::getInstance()->getHeight(), 
					0.0f, 1.0f, 1.0f, 0.0f, gameplay::Vector4::one(), false);
	background->finish();

	//draw the menu
	form->draw();
}

void Menu::controlEvent( gameplay::Control* control, gameplay::Control::Listener::EventType  evt )
{
	if (!visible) {
		return;
	}

	if (control == new_game_button) {
		//create a new game
		((words*) gameplay::Game::getInstance())->NewGame();
		//hide this 
		this->Hide();
	}
}

int Menu::getWidth()
{
	return form->getWidth();
}

int Menu::getHeight()
{
	return form->getHeight();
}

void Menu::Update( float dt )
{
	form->update(dt);
}

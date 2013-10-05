#include "game.hpp"


#include "letter_controller.hpp"
#include "board/board_solver.hpp"
#include "selected_text_label.hpp"
#include "score_controller.hpp"
#include "timer_controller.hpp"
#include "menu_icon_controller.hpp"
#include "../statistics.hpp"
#include "../ext/scene_manager.hpp"

Words::Game* Words::Game::instance = NULL;

bool Words::Game::HandleTouchDownEvent(gameplay::Ray& ray, int x, int y) 
{
	if (LetterController::HandleTouchDownEvent(ray, x, y)) {
		return true;
	} else if (MenuIconController::HandleTouchDownEvent(ray, x, y)) {
		return true;
	} 

	return false;
}

bool Words::Game::HandleTouchUpEvent( gameplay::Ray& ray, int x, int y )
{
	//pass along the touch event to the controllers who are listening
	LetterController::HandleTouchUpEvent(x, y);

	return false;
}

void Words::Game::Init(gameplay::Scene* scene)
{
	Words::Game::instance = new Words::Game();
	Words::Game::instance->scene = scene;

	DiceManager::Init();
	LetterController::Init(scene);
	Board::Init(scene->findNode("letter_tile"));
	SelectedTextLabel::Init();
	SelectedTextConnector::Init();
	ScoreController::Init();
	TimerController::Init();
	BoardSolver::Init();
	MenuIconController::Init();
}

Words::Game* Words::Game::Get()
{
	return Words::Game::instance;
}

void Words::Game::Update( float elapsedTime )
{
	ScoreController::Update(elapsedTime);
	TimerController::Update(elapsedTime);
	LetterController::get()->Update(elapsedTime);
	SelectedTextLabel::get()->Update(elapsedTime);
}

void Words::Game::Render()
{
	gameplay::Game* game = gameplay::Game::getInstance();

	// Clear the color and depth buffers
	game->clear(game->CLEAR_COLOR_DEPTH, gameplay::Vector4(1, 1, 1, 1), 1.0f, 0);

	//render selected text
	SelectedTextLabel::get()->Render();

	//render letter grid
	LetterController::Render(this->scene->getActiveCamera());

	//render score and timer
	ScoreController::Render();
	TimerController::Render();

	//render the menu icon
	MenuIconController::Render();
}

void Words::Game::NewGame()
{
	//reset statistics
	Statistics::StartNewRound();

	//initialize the letter provider
	DiceManager::ReassignDice();

	//initialize the actual letters
	LetterController::InitializeLetters();

	//set the score to 0
	ScoreController::ResetScore();

	//reset time and kick if of
	TimerController::Reset();
	TimerController::StartTimer();
}

void Words::Game::GameOver()
{
	Statistics::RoundComplete(ScoreController::RoundPoints());
	SceneManager::get()->GotoMenuScene(true);
}


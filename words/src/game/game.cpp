#include "game.hpp"


#include "../statistics.hpp"
#include "../ext/scene_manager.hpp"

#include "views/board_view.hpp"
#include "views/selected_text_label.hpp"
#include "views/score_view.hpp"
#include "views/timer_controller.hpp"
#include "views/menu_icon_controller.hpp"
#include "views/time_tank_view.hpp"
#include "board/board_solver.hpp"

Words::Game* Words::Game::instance = NULL;

bool Words::Game::HandleTouchDownEvent(gameplay::Ray& ray, int x, int y) 
{
	if (BoardView::HandleTouchDownEvent(ray, x, y)) {
		return true;
	} else if (MenuIconController::HandleTouchDownEvent(ray, x, y)) {
		return true;
	} 

	return false;
}

bool Words::Game::HandleTouchUpEvent( gameplay::Ray& ray, int x, int y )
{
	//pass along the touch event to the controllers who are listening
	BoardView::HandleTouchUpEvent(x, y);

	return false;
}

void Words::Game::Init(gameplay::Scene* scene)
{
	Words::Game::instance = new Words::Game();
	Words::Game::instance->scene = scene;

	DiceManager::Init();
	BoardView::Init(scene);
	Board::Init(scene->findNode("letter_tile"));
	SelectedTextLabel::Init();
	SelectedTextConnector::Init();
	ScoreView::Init();
	TimerController::Init();
	BoardSolver::Init();
	MenuIconController::Init();
	TimerController::Init();
	//TimeTankView::Init();
}

Words::Game* Words::Game::Get()
{
	return Words::Game::instance;
}

void Words::Game::Update( float elapsedTime )
{
	ScoreView::Update(elapsedTime);
	TimerController::Update(elapsedTime);
	BoardView::get()->Update(elapsedTime);
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
	BoardView::Render(this->scene->getActiveCamera());

	//render score and timer
	ScoreView::Render();
	TimerController::Render();

	//render the menu icon
	MenuIconController::Render();

	//render the time tanks
	//TimeTankView::Render();
}

void Words::Game::NewGame()
{
	//reset statistics
	Statistics::StartNewRound();

	//initialize the letter provider
	DiceManager::ReassignDice();

	//initialize the actual letters
	BoardView::InitializeLetters();

	//set the score to 0
	ScoreView::ResetScore();

	//reset time and kick if of
	TimerController::Reset();
	TimerController::StartTimer();
}

void Words::Game::GameOver()
{
	Statistics::RoundComplete(ScoreView::RoundPoints());
	SceneManager::get()->GotoMenuScene(true);
}

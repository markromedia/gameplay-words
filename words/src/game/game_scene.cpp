#include "game_scene.hpp"


#include "../statistics.hpp"
#include "../ext/scene_manager.hpp"

#include "game_state_model.hpp"
#include "views/board_view.hpp"
#include "views/selected_text_label.hpp"
#include "views/score_view.hpp"
#include "views/timer_controller.hpp"
#include "views/menu_icon.hpp"
#include "views/time_tank_view.hpp"
#include "board/board_solver.hpp"

GameScene* GameScene::instance = NULL;

bool GameScene::HandleTouchDownEvent(gameplay::Ray& ray, int x, int y) 
{
	if (BoardView::HandleTouchDownEvent(ray, x, y)) {
		return true;
	} else if (MenuIcon::HandleTouchDownEvent(ray, x, y)) {
		return true;
	} 

	return false;
}

bool GameScene::HandleTouchUpEvent( gameplay::Ray& ray, int x, int y )
{
	//pass along the touch event to the controllers who are listening
	BoardView::HandleTouchUpEvent(x, y);

	return false;
}

void GameScene::Init(gameplay::Scene* scene)
{
	GameScene::instance = new GameScene();
	GameScene::instance->scene = scene;

	GameStateModel::Reset();
	DiceManager::Init();
	BoardView::Init(scene);
	Board::Init(scene->findNode("letter_tile"));
	SelectedTextLabel::Init();
	SelectedTextConnector::Init();
	ScoreView::Init();
	TimerController::Init();
	BoardSolver::Init();
	MenuIcon::Init();
	TimerController::Init();
	TimeTankView::Init();
}

GameScene* GameScene::Get()
{
	return GameScene::instance;
}

void GameScene::Update( float elapsedTime )
{
	GameStateModel::Update(elapsedTime);
	if (GameStateModel::TimeRemaining() <= 0) {
		GameOver();
		return;
	}

	ScoreView::Update(elapsedTime);
	TimerController::Update(elapsedTime);
	BoardView::get()->Update(elapsedTime);
	SelectedTextLabel::get()->Update(elapsedTime);
	TimeTankView::Update(elapsedTime);
}

void GameScene::Render()
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
	MenuIcon::Render();

	//render the time tanks
	TimeTankView::Render();
}

void GameScene::NewGame()
{
	//reset game state
	GameStateModel::Reset();

	//reset statistics
	Statistics::StartNewRound();

	//initialize the letter provider
	DiceManager::ReassignDice();

	//initialize the actual letters
	BoardView::InitializeLetters();

	//initialize powersups/time tanks
	TimeTankView::Reset();

}

void GameScene::GameOver()
{
	Statistics::RoundComplete(GameStateModel::GamePoints());
	SceneManager::get()->GotoMenuScene(true);
}


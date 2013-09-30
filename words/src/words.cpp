#include "words.h"

#include "renderable_node_repository.hpp"
#include "letter_controller.hpp"
#include "board_solver.hpp"
#include "selected_text_label.hpp"
#include "score_controller.hpp"
#include "timer_controller.hpp"
#include "menu.hpp"
#include "dice_manager.hpp"
#include "board.hpp"
#include "selected_text_connector.hpp"
#include "statistics.hpp"
#include "rest_handler.hpp"
#include "menu_icon_controller.hpp"


// Declare our game instance
words game;

words::words()
    : scene(NULL)
{
}

void words::initialize()
{
    // Load game scene from file
    Bundle* bundle = Bundle::create("res/words_scene.gpb");
    scene = bundle->loadScene();
    SAFE_RELEASE(bundle);

	//create scene camera	
	camera_node = scene->addNode("main_camera");
	Camera *camera = Camera::createPerspective(60.0f, (float)getWidth() / (float)getHeight(), 1.0f, 5000);
	camera_node->setCamera(camera);
	scene->setActiveCamera(camera);

	// Display the gameplay splash screen for at least 1.5 second.
	displayScreen(this, &words::drawSplash, NULL, 1500L);

	//create the camera control
	camera_control = new CameraControl(camera_node);

	//init font for the framerate
	framerate = Font::create("res/myriadpro50.gpb");

	//init the menu
	this->menu = new Menu();
	
	//init singletons
	RenderableNodeRepository::Init(scene);
	DiceManager::Init();
	LetterController::Init(scene);
	Board::Init(scene->findNode("letter_tile"));
	SelectedTextLabel::Init();
	SelectedTextConnector::Init();
	ScoreController::Init();
	TimerController::Init();
	BoardSolver::Init();
	MenuIconController::Init();
	Statistics::Init();
	RestHandler::Init();

	//this->menu->Show(false);

	//TODO remove
	//BoardSolver::CreatePrecalculatedBoards();

	//init with a new game
	NewGame();
}

void words::NewGame()
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

void words::GameOver()
{
	Statistics::RoundComplete(ScoreController::RoundPoints());
	menu->Show(true);
}


void words::ShowMenu()
{
	menu->Show(false);
}

void words::finalize()
{
    SAFE_RELEASE(scene);
}

void words::update(float elapsedTime)
{
    //update everyone
    menu->Update(elapsedTime);

	if (!menu->IsVisible())
	{
		ScoreController::Update(elapsedTime);
		TimerController::Update(elapsedTime);
		LetterController::get()->Update(elapsedTime);
		SelectedTextLabel::get()->Update(elapsedTime);
	}
}

void words::render(float elapsedTime)
{
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4(1, 1, 1, 1), 1.0f, 0);


	//draw framerate
	drawFrameRate(getFrameRate());

	if (menu->IsVisible()) {
		this->menu->Render();
	} else {
		//render selected text
		SelectedTextLabel::get()->Render();

		//render letter grid
		LetterController::Render(scene->getActiveCamera());

		//render score and timer
		ScoreController::Render();
		TimerController::Render();

		//render the menu icon
		MenuIconController::Render();
	}
}

void words::drawSplash(void* param)
{
	clear(CLEAR_COLOR_DEPTH, Vector4(1, 1, 1, 1), 1.0f, 0);
	SpriteBatch* batch = SpriteBatch::create("res/png/logo.png");
	batch->start();
	batch->draw(getWidth() * 0.5f, getHeight() * 0.5f, 0.0f, 512.0f, 128.0f, 0.0f, 1.0f, 1.0f, 0.0f, Vector4::one(), true);
	batch->finish();
	SAFE_DELETE(batch);
}

void words::drawFrameRate(unsigned int fps)
{
	char buffer[30];
	sprintf(buffer, "FPS: %u", fps);
	framerate->start();
	framerate->drawText(buffer, 10, getHeight() - 30, Vector4(0,0,0,1), 28);
	framerate->finish();
}


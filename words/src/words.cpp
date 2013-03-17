#include "words.h"

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

	// Display the gameplay splash screen for at least 3 second.
	displayScreen(this, &words::drawSplash, NULL, 3000L);

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
	ScoreController::Init();
	TimerController::Init();
	BoardSolver::Init();
	SelectedTextConnector::Init();

	//TODO remove
	//BoardSolver::CreatePrecalculatedBoards();

	//init with a new game
	NewGame();
}

void words::NewGame()
{
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
	menu->Show();
}

void words::finalize()
{
    SAFE_RELEASE(scene);
}

void words::update(float elapsedTime)
{
    //update everyone
    menu->Update(elapsedTime);
    ScoreController::Update(elapsedTime);
	TimerController::Update(elapsedTime);
	LetterController::get()->Update(elapsedTime);
	SelectedTextLabel::get()->Update(elapsedTime);
}

void words::render(float elapsedTime)
{
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4(1, 1, 1, 1), 1.0f, 0);

	//draw framerate
	drawFrameRate(getFrameRate());

	//render selected text
	SelectedTextLabel::get()->Render();

	//render letter grid
    LetterController::Render(scene->getActiveCamera());

	//render score and timer
	ScoreController::Render();
	TimerController::Render();

	//tell menu to render (if its visible)
	menu->Render();
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


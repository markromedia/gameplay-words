#include "words.h"

#include "renderable_node_repository.hpp"
#include "game/game_scene.hpp"
#include "statistics.hpp"
#include "ext/rest_handler.hpp"
#include "ext/scene_manager.hpp"


// Declare our game instance
words game;

words::words()
    : scene(NULL)
{
}

void words::initialize()
{
    // Load game scene from file
    gameplay::Bundle* bundle = gameplay::Bundle::create("res/words_scene.gpb");
    scene = bundle->loadScene();
    SAFE_RELEASE(bundle);

	//create scene camera	
	camera_node = scene->addNode("main_camera");
	gameplay::Camera *camera = gameplay::Camera::createPerspective(60.0f, (float)getWidth() / (float)getHeight(), 1.0f, 5000);
	camera_node->setCamera(camera);
	scene->setActiveCamera(camera);

	// Display the gameplay splash screen for at least 1.5 second.
	displayScreen(this, &words::drawSplash, NULL, 1500L);

	//create the camera control
	CameraControl::Init(camera, camera_node);

	//init font for the framerate
	framerate = gameplay::Font::create("res/myriadpro50.gpb");

	//init the renderable repo
	RenderableNodeRepository::Init(scene);

	//init the game scene
	GameScene::Init(scene);

	//init the scene manager
	SceneManager::Init();

	//init singletons
	Statistics::Init();
	RestHandler::Init();

	//TODO remove
	//BoardSolver::CreatePrecalculatedBoards();

	//start a new game
	SceneManager::get()->StartNewGame();
}

void words::finalize()
{
    SAFE_RELEASE(scene);
}

void words::update(float elapsedTime)
{
	SceneManager::get()->Update(elapsedTime);
}

void words::render(float elapsedTime)
{
	SceneManager::get()->Render();

	//draw framerate
	drawFrameRate(getFrameRate());

}

void words::drawSplash(void* param)
{
	clear(CLEAR_COLOR_DEPTH, Vector4(1, 1, 1, 1), 1.0f, 0);
	gameplay::SpriteBatch* batch = gameplay::SpriteBatch::create("res/png/logo.png");
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
	framerate->drawText(buffer, 10, getHeight() - 30, gameplay::Vector4(0,0,0,1), 28);
	framerate->finish();
}


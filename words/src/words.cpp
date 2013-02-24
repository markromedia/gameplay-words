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
	
	//tile test
	RenderableNodeRepository::Init(scene);
	LetterController::Init(scene);
}

void words::finalize()
{
    SAFE_RELEASE(scene);
}

void words::update(float elapsedTime)
{
    // Rotate model
    //scene->findNode("Box01")->rotateX(MATH_DEG_TO_RAD((float)elapsedTime / 1000.0f * 180.0f));
    //tile.Update(scene->getActiveCamera(), elapsedTime);
}

void words::render(float elapsedTime)
{
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4::one(), 1.0f, 0);

    // Visit all the nodes in the scene for drawing
    //scene->visit(this, &words::drawScene);
    LetterController::Render(scene->getActiveCamera());
}

bool words::drawScene(Node* node)
{
    // If the node visited contains a model, draw it
    Model* model = node->getModel(); 
    if (model)
    {
        model->draw();
    }
    return true;
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


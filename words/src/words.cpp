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

	//create the camera control
	camera_control = new CameraControl(camera_node);
	
	//tile test
	RenderableNodeRepository::Init(scene);
	LetterManager::Init(scene);
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
    clear(CLEAR_COLOR_DEPTH, Vector4::zero(), 1.0f, 0);

    // Visit all the nodes in the scene for drawing
    //scene->visit(this, &words::drawScene);
    LetterManager::Render(scene->getActiveCamera());
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

void words::keyEvent(Keyboard::KeyEvent evt, int key)
{
    if (evt == Keyboard::KEY_PRESS)
    {
        switch (key)
        {
        case Keyboard::KEY_ESCAPE:
            exit();
            break;
        }
    }
}

void words::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
    switch (evt)
    {
    case Touch::TOUCH_PRESS:
        break;
    case Touch::TOUCH_RELEASE:
        break;
    case Touch::TOUCH_MOVE:
        break;
    };
}

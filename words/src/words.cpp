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
    Bundle* bundle = Bundle::create("res/letter.gpb");
    scene = bundle->loadScene();
    SAFE_RELEASE(bundle);

	//create scene camera	
	camera_node = scene->addNode("main_camera");
	Camera *camera = Camera::createPerspective(60.0f, (float)getWidth() / (float)getHeight(), 1.0f, 5000);
	camera_node->setCamera(camera);
	scene->setActiveCamera(camera);

	//create the camera control
	camera_control = new CameraControl(camera_node);
    
	
	int y_offset = -40;
	
	//set up the letter
	box_node = scene->findNode("Box09");
	Material *material = box_node->getModel()->setMaterial("res/words.material#letter");
	box_node->setTranslation(-90, -70 + y_offset, 0);

	//row 1 (from bottom)
	initLetter(-30, -70 + y_offset, 0, "Box01");
	initLetter(30, -70 + y_offset, 0, "Box02");
	initLetter(90, -70 + y_offset, 0, "Box03");

	//row 2 (from bottom)
	initLetter(-90, -10 + y_offset, 0, "Box04");
	initLetter(-30, -10 + y_offset, 0, "Box05");
	initLetter(30, -10 + y_offset, 0, "Box06");
	initLetter(90, -10 + y_offset, 0, "Box07");

	//row 3 (from bottom)
	initLetter(-90, 50 + y_offset, 0, "Box08");
	initLetter(-30, 50 + y_offset, 0, "Box10");
	initLetter(30, 50 + y_offset, 0, "Box11");
	initLetter(90, 50 + y_offset, 0, "Box12");

	//row 4 (from bottom)
	initLetter(-90, 110 + y_offset, 0, "Box13");
	initLetter(-30, 110 + y_offset, 0, "Box14");
	initLetter(30, 110 + y_offset, 0, "Box15");
	initLetter(90, 110 + y_offset, 0, "Box16");
}

void words::initLetter(int x, int y, int z, const char* name) {
	Node* new_node = this->box_node->clone();
	new_node->setId(name);
	new_node->setTranslation(x, y, z);
	scene->addNode(new_node);
}

void words::finalize()
{
    SAFE_RELEASE(scene);
}

void words::update(float elapsedTime)
{
    // Rotate model
    //scene->findNode("Box01")->rotateX(MATH_DEG_TO_RAD((float)elapsedTime / 1000.0f * 180.0f));
}

void words::render(float elapsedTime)
{
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4::one(), 1.0f, 0);

    // Visit all the nodes in the scene for drawing
    scene->visit(this, &words::drawScene);
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

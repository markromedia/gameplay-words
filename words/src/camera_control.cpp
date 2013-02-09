#include "camera_control.hpp"

const int CAMERA_VELOCITY = 10;

CameraControl::CameraControl(Node* camera_node) {
	this->camera_node = camera_node;
	camera_move_direction = NONE;

	camera_target.x = 0; camera_target.y = 0; camera_target.z = 400; 
	camera_node->translate(camera_target);
}

void CameraControl::Update(float delta) 
{
	if (is_looking_at_origin) 
	{
		Matrix m;
		Matrix::createLookAt(camera_node->getTranslation(), Vector3::zero(), Vector3::unitY(), &m);
		m.transpose();
		Quaternion q;
		m.getRotation(&q);
		camera_node->setRotation(q);
	}

	if (camera_move_direction != NONE) 
	{
		if (camera_move_direction & LEFT)
			camera_target += camera_node->getRightVector() * -CAMERA_VELOCITY;
		if (camera_move_direction & RIGHT)
			camera_target += camera_node->getRightVector() * CAMERA_VELOCITY;
		if (camera_move_direction & FORWARD)
			camera_target += camera_node->getForwardVector() * CAMERA_VELOCITY;
		if (camera_move_direction & BACKWARDS)
			camera_target += camera_node->getForwardVector() * -CAMERA_VELOCITY;

		//round target
		camera_target.x = (int) camera_target.x;
		camera_target.y = (int) camera_target.y;
		camera_target.z = (int) camera_target.z;
	}

	camera_node->translateSmooth(camera_target, delta, 100);
	camera_node->getMatrix();
}

void CameraControl::KeyEventHandler(Keyboard::KeyEvent evt, int key)
{
	if (evt == Keyboard::KEY_PRESS)
	{
		switch (key)
		{
		case Keyboard::KEY_W: 
		case Keyboard::KEY_UP_ARROW: 
			camera_move_direction |= FORWARD;
			break;
		case Keyboard::KEY_S: 
		case Keyboard::KEY_DOWN_ARROW: 
			camera_move_direction |= BACKWARDS;
			break;
		case Keyboard::KEY_A: 
		case Keyboard::KEY_LEFT_ARROW: 
			camera_move_direction |= LEFT;
			break;
		case Keyboard::KEY_D: 
		case Keyboard::KEY_RIGHT_ARROW: 
			camera_move_direction |= RIGHT;
			break;
		case Keyboard::KEY_SHIFT: 
			is_looking_at_origin = true;
			break;
		}
	}

	if (evt == Keyboard::KEY_RELEASE)
	{
		switch (key)
		{
		case Keyboard::KEY_W: 
		case Keyboard::KEY_UP_ARROW: 
			camera_move_direction &= ~FORWARD;
			break;
		case Keyboard::KEY_S: 
		case Keyboard::KEY_DOWN_ARROW: 
			camera_move_direction &= ~BACKWARDS;
			break;
		case Keyboard::KEY_A: 
		case Keyboard::KEY_LEFT_ARROW: 
			camera_move_direction &= ~LEFT;
			break;
		case Keyboard::KEY_D: 
		case Keyboard::KEY_RIGHT_ARROW: 
			camera_move_direction &= ~RIGHT;
			break;
		case Keyboard::KEY_SHIFT: 
			is_looking_at_origin = false;
			break;
		}
	}
}

void CameraControl::HandleMouseEvent(Mouse::MouseEvent evt, int x, int y, int wheelDelta) 
{
	Vector3 v = Vector3(camera_node->getTranslation());
	//move to origin
	camera_node->setTranslation(0, 0, 0);
	camera_node->rotateX(MATH_DEG_TO_RAD(y));
	camera_node->rotateY(MATH_DEG_TO_RAD(x));
	camera_node->getMatrix();//flush changes
	//reapply translation
	camera_node->setTranslation(v);
}
#include "camera_control.hpp"

const int CAMERA_VELOCITY = 10;

CameraControl* CameraControl::instance;

CameraControl::CameraControl(Camera* camera, Node* camera_node) {
	this->camera_node = camera_node;
	this->camera = camera;

	camera_move_direction = NONE;
	camera_target.x = 0; camera_target.y = 0; camera_target.z = 290; 
	camera_node->setTranslation(camera_target);
}

void CameraControl::Init( gameplay::Camera* camera, Node* camera_node)
{
	CameraControl::instance = new CameraControl(camera, camera_node);
}

CameraControl* CameraControl::Get()
{
	return CameraControl::instance;
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

void CameraControl::CreateBillboardHelper(const Vector3& objectPosition, const Vector3& cameraPosition,
								 const Vector3& cameraUpVector, const Vector3& cameraForwardVector,
								 Matrix* dst)
{
	Vector3 delta(objectPosition, cameraPosition);
	bool isSufficientDelta = false;//delta.lengthSquared() > MATH_EPSILON;

	dst->setIdentity();
	dst->m[3] = objectPosition.x;
	dst->m[7] = objectPosition.y;
	dst->m[11] = objectPosition.z;

	// As per the contracts for the 2 variants of createBillboard, we need
	// either a safe default or a sufficient distance between object and camera.
	Vector3 target = isSufficientDelta ? cameraPosition : (objectPosition - cameraForwardVector);

	// A billboard is the inverse of a lookAt rotation
	Matrix lookAt;
	Matrix::createLookAt(objectPosition, target, cameraUpVector, &lookAt);
	dst->m[0] = lookAt.m[0];
	dst->m[1] = lookAt.m[4];
	dst->m[2] = lookAt.m[8];
	dst->m[4] = lookAt.m[1];
	dst->m[5] = lookAt.m[5];
	dst->m[6] = lookAt.m[9];
	dst->m[8] = lookAt.m[2];
	dst->m[9] = lookAt.m[6];
	dst->m[10] = lookAt.m[10];
}

void CameraControl::CreateBillboardHelper( const gameplay::Vector3& objectPosition, gameplay::Matrix* dst )
{
	Camera* c = CameraControl::instance->camera;
	CameraControl::CreateBillboardHelper(objectPosition, c->getNode()->getTranslationWorld(), c->getNode()->getUpVectorWorld(), c->getNode()->getForwardVector(), dst);
}



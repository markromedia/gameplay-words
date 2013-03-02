#include "input_event_handler.hpp"


using namespace gameplay;

InputEventHandler* InputEventHandler::instance = NULL;

void InputEventHandler::_checkCreateInstance()
{
	if (instance == NULL) {
		instance = new InputEventHandler();
		instance->enabled = true;
	}
}

InputEventHandler* InputEventHandler::get()
{
	_checkCreateInstance();
	return instance;
}

bool InputEventHandler::handleTouchEvent(words* game, int x, int y )
{
	if (!enabled) {
		return false;
	}

	if (touchState == TOUCH_DOWN) {
		Node* cameraNode = game->scene->getActiveCamera()->getNode();
		Ray ray;
		game->scene->getActiveCamera()->pickRay(game->getViewport(), x, y, &ray);

		//pass along the touch event to the controllers who are listening
		if (LetterController::HandleTouchDownEvent(ray, x, y)) {
			return true;
		} else {
			//ADD MORE
		}
	} else if (touchState == TOUCH_UP) { 
		//pass along the touch event to the controllers who are listening
		LetterController::HandleTouchUpEvent();
	}


	return false;
}

void InputEventHandler::touchEvent(words* game,  gameplay::Touch::TouchEvent evt, int x, int y, unsigned int contactIndex )
{
	switch (evt)
	{
	case Touch::TOUCH_PRESS:
		touchState = TOUCH_DOWN;
		handleTouchEvent(game, x, y);
		break;
	case Touch::TOUCH_RELEASE:
		touchState = TOUCH_UP;
		handleTouchEvent(game, x, y);
		break;
	case Touch::TOUCH_MOVE:
		handleTouchEvent(game, x, y);
		break;
	};
}

bool InputEventHandler::mouseEvent(words* game, gameplay::Mouse::MouseEvent evt, int x, int y, int wheelDelta )
{
	switch (evt)
	{
	case Mouse::MOUSE_PRESS_LEFT_BUTTON :
		touchState = TOUCH_DOWN;
		return handleTouchEvent(game, x, y);
		break;
	case Mouse::MOUSE_RELEASE_LEFT_BUTTON :
		touchState = TOUCH_UP;
		return handleTouchEvent(game, x, y);
		break;
	};

	return false;
}

void InputEventHandler::keyEvent(words* game, gameplay::Keyboard::KeyEvent evt, int key )
{
	if (evt == Keyboard::KEY_PRESS)
	{
		switch (key)
		{
		case Keyboard::KEY_ESCAPE:
			game->exit();
			break;
		}
	}
}

void InputEventHandler::SetEnabled( bool enabled)
{
	this->enabled = enabled;
}

/************************************************************************/
/* Below is the partial implementation of the game which just handles   */
/* InputEvents. They delegate directly to the above methods             */
/************************************************************************/
void words::touchEvent( gameplay::Touch::TouchEvent evt, int x, int y, unsigned int contactIndex )
{
	InputEventHandler::get()->touchEvent(this, evt, x, y, contactIndex);
}

bool words::mouseEvent( gameplay::Mouse::MouseEvent evt, int x, int y, int wheelDelta )
{
	return InputEventHandler::get()->mouseEvent(this, evt, x, y, wheelDelta);
}

void words::keyEvent( gameplay::Keyboard::KeyEvent evt, int key )
{
	InputEventHandler::get()->keyEvent(this, evt, key);
}

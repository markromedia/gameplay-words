#ifndef words_H_
#define words_H_

#include "gameplay.h"
#include "camera_control.hpp"
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

using namespace gameplay;

class Menu;

#define APP_VERSION std::string("0.1.0")

/**
 * Main game class.
 */
class words: public Game
{
public:
	/// @summary	The scene.
	Scene* scene;

    /**
     * Constructor.
     */
    words();

    /**
     * @see Game::keyEvent
     */
	void keyEvent(Keyboard::KeyEvent evt, int key);
	
    /**
     * @see Game::touchEvent
     */
    void touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);

		
    /**
     * @see Game::mouseEvent
     */
	bool mouseEvent(Mouse::MouseEvent evt, int x, int y, int wheelDelta);

	/// Sets up the game for a new game
	void NewGame();

	/// Called when a game is over
	void GameOver();
protected:

    /**
     * @see Game::initialize
     */
    void initialize();

    /**
     * @see Game::finalize
     */
    void finalize();

    /**
     * @see Game::update
     */
    void update(float elapsedTime);

    /**
     * @see Game::render
     */
    void render(float elapsedTime);

private:

	/// @summary	The camera node.
	Node* camera_node;

	/// @summary	The camera control.
	CameraControl* camera_control;

	/// @summary	The menu.
	Menu* menu;

	/// Draw splash.
	/// @param [in,out]	param	If non-null, the parameter.
	void drawSplash(void* param);

	void drawFrameRate(unsigned int fps);

	/// @summary	The framerate font.
	Font* framerate;
};

#endif

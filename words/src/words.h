#ifndef words_H_
#define words_H_

#include "gameplay.h"
#include "camera_control.hpp"
#include "renderable_node_repository.hpp"
#include "letter_controller.hpp"
#include "word_checker.hpp"
#include "selected_text_label.hpp"
#include "score_controller.hpp"
#include "timer_controller.hpp"

using namespace gameplay;

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

    /**
     * Draws the scene each frame.
     */
    bool drawScene(Node* node);

	/// @summary	The camera node.
	Node* camera_node;

	/// @summary	The camera control.
	CameraControl* camera_control;

	void drawSplash(void* param);
};

#endif

#ifndef words_H_
#define words_H_

#include "gameplay.h"
#include "camera_control.hpp"

using namespace gameplay;

/**
 * Main game class.
 */
class words: public Game
{
public:

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

	void initLetter(int x, int y, int z, const char* name);

	/// @summary	The scene.
	Scene* scene;

	/// @summary	The box node.
	Node* box_node;

	/// @summary	The camera node.
	Node* camera_node;

	/// @summary	The camera control.
	CameraControl* camera_control;
};

#endif

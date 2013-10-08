#ifndef words_H_
#define words_H_

#include "gameplay.h"
#include "camera_control.hpp"

class Menu;

#define APP_VERSION std::string("0.1.0")

/**
 * Main game class.
 */
class words: public Game
{
public:
	/// @summary	The scene.
	gameplay::Scene* scene;

    /**
     * Constructor.
     */
    words();

    /**
     * @see Game::keyEvent
     */
	void keyEvent(gameplay::Keyboard::KeyEvent evt, int key);
	
    /**
     * @see Game::touchEvent
     */
    void touchEvent(gameplay::Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);

		
    /**
     * @see Game::mouseEvent
     */
	bool mouseEvent(gameplay::Mouse::MouseEvent evt, int x, int y, int wheelDelta);
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
	gameplay::Node* camera_node;

	/// Draw splash.
	/// @param [in,out]	param	If non-null, the parameter.
	void drawSplash(void* param);

	void drawFrameRate(unsigned int fps);

	/// @summary	The framerate font.
	gameplay::Font* framerate;
};

#endif

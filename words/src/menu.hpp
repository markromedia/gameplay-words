#ifndef __MENU__hpp
#define __MENU__hpp

#include "gameplay.h"
#include "timer_controller.hpp"

class Menu : public gameplay::Control::Listener {
private:
	/// @summary	The form.
	gameplay::Form* form;

	/// @summary	The new game button.
	gameplay::Button* new_game_button;

	/// @summary	The container.
	gameplay::Container* container;

	/// @summary	The background.
	gameplay::SpriteBatch* background;

	/// @summary	true to show, false to hide.
	bool visible;
public:
	/// Constructor.
	///
	/// @param [in,out]	game	If non-null, the game.
	Menu();

	/// Hides the menu.
	void Hide();

	/// Shows the menu. Also stops inputs
	/// from going to the input handler
	void Show();

	/// Gets the width.
	/// @return	The width.
	int getWidth();

	/// Gets the height.
	/// @return	The height.
	int getHeight();

	/// Renders the menu.
	void Render();

	/// Updates the given dt.
	/// @param	dt	The dt.
	void Update(float dt);

	/// from Control::Listener
	void controlEvent( gameplay::Control* control, gameplay::Control::Listener::EventType evt );

};

#endif  // __MENU__hpp
#ifndef __MENU__hpp
#define __MENU__hpp

#include "gameplay.h"
#include "timer_controller.hpp"
#include "librocket//RocketInterfaces.h"
#include <Rocket/Core.h>

class Menu {
private:
	/// @summary	The background.
	gameplay::SpriteBatch* menu_items;

	/// @summary	The numbers.
	gameplay::SpriteBatch* menu_numbers;

	/// @summary	true to show, false to hide.
	bool visible;

	/// @summary	true if this object is game over.
	bool is_game_over;

	/// @summary	The points text coords
	static float menu_items_coords[7][4];

	/// @summary	The menu numbers coords[ 4].
	static float menu_numbers_coords[10][4];

	/// @summary	The button positions[ 2].
	float button_positions[2][2];

	void Menu::drawItem( int p_idx, int x, int y );

	void Menu::drawNumber( int number, int x, int y );

	RocketGP3DFile _fileInterface;
	RocketGP3DSystem _systemInterface;
	RocketGP3Render _renderInterface;
	Rocket::Core::Context *_rocketContext;
public:
	/// Constructor.
	///
	/// @param [in,out]	game	If non-null, the game.
	Menu();

	/// Query if this object is visible.
	/// @return	true if visible, false if not.
	bool IsVisible();

	/// Hides the menu.
	void Hide();

	/// Shows the menu. Also stops inputs
	/// from going to the input handler
	void Show(bool game_over_screen);

	/// Renders the menu.
	void Render();

	/// Updates the given dt.
	/// @param	dt	The dt.
	void Update(float dt);

	bool HandleTouchDownEvent(gameplay::Ray& ray, int x, int y );

	/// Initializes the rocket.
	void initializeRocket();
};

#endif  // __MENU__hpp
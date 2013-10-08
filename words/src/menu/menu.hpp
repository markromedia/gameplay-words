#ifndef __MENU__hpp
#define __MENU__hpp

#include "gameplay.h"
#include "../game/views/timer_controller.hpp"
#include "../scene.hpp"
//#include "librocket//RocketInterfaces.h"
//#include <Rocket/Core.h>

class Menu : public Words::Scene {
private:
	/// @summary	The background.
	gameplay::SpriteBatch* menu_items;

	/// @summary	The numbers.
	gameplay::SpriteBatch* menu_numbers;

	/// @summary	true if this object is game over.
	bool is_game_over;

	/// @summary	The points text coords
	static float menu_items_coords[7][4];

	/// @summary	The menu numbers coords[ 4].
	static float menu_numbers_coords[10][4];

	/// @summary	The button positions[ 2].
	float button_positions[2][2];

	void drawItem( int p_idx, int x, int y );

	void drawNumber( int number, int x, int y );

	//RocketGP3DFile _fileInterface;
	//RocketGP3DSystem _systemInterface;
	//RocketGP3Render _renderInterface;
	//Rocket::Core::Context *_rocketContext;
public:
	/// Constructor.
	///
	/// @param [in,out]	game	If non-null, the game.
	Menu();

	/// <inheritdoc />
	virtual bool Menu::HandleTouchDownEvent( gameplay::Ray& ray, int x, int y );

	/// <inheritdoc />
	virtual bool HandleTouchUpEvent(gameplay::Ray& ray, int x, int y) ;

	/// <inheritdoc />
	virtual void Update(float elapsedTime);

	/// <inheritdoc />
	virtual void Render();

	/// Initializes the rocket.
	void initializeRocket();

	/// Sets the is game over.
	/// @param	is_game_over	true if this object is game over.
	void SetIsGameOver(bool is_game_over);
};

#endif  // __MENU__hpp
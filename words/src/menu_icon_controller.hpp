#ifndef __MENU_ICON_CONTROLLER__hpp
#define __MENU_ICON_CONTROLLER__hpp

#include <algorithm>
#include <set>
#include <sstream>

#include "gameplay.h"

class MenuIconController {
private:
	/// Default constructor.
	MenuIconController();

	/// @summary	The numbers.
	gameplay::SpriteBatch* menu_icon;


	/// @summary	true to show, false to hide.
	bool visible;

	/// @summary	The instance.
	static MenuIconController* instance;

	/// @summary	Source rectangle.
	gameplay::Rectangle src_rect;

	/// @summary	dest rectangle.
	gameplay::Rectangle dest_rect;

	float x_pos, y_pos, icon_width, icon_height;
public:
	/// Initialises this object.
	static void Init();

	/// Handles the touch down event.
	///
	/// @param [in,out]	ray	the calculated ray.
	/// @param	x		   	The x coordinate.
	/// @param	y		   	The y coordinate.
	///
	/// @return	true if it succeeds, false if it fails.
	static bool HandleTouchDownEvent(gameplay::Ray& ray, int x, int y);

	/// Renders this object.
	static void Render();

	/// Sets a visibility.
	///
	/// @param	visible	true to show, false to hide.
	static void SetVisibility(bool visible);

	/// Query if this object is visible.
	/// @return	true if visible, false if not.
	static bool IsVisible();
};

#endif  // __MENU_ICON_CONTROLLER__hpp
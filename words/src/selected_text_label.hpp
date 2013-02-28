#ifndef __SELECTED_TEXT_LABEL__hpp
#define __SELECTED_TEXT_LABEL__hpp

#include <vector>

#include "gameplay.h"
#include "renderable_node_repository.hpp"

class SelectedTextLabel {
private:
	enum ANIMATION_MODE { NONE, SHAKING, SUCESS};

	/// @summary	The used to draw the text itself.
	gameplay::Font* font;

	/// @summary	Size of the font.
	unsigned int font_size;

	/// @summary	The string to draw.
	std::string string_to_draw;

	/// Converts a str to an upper.
	/// @param [in,out]	str	The.
	void toUpper(std::string& str);

	/// @summary	Time of the total visible.
	float total_visible_time;

	/// @summary	true to do render.
	bool do_render;

	/// the batches used for the background
	gameplay::SpriteBatch* left_bg;
	gameplay::SpriteBatch* right_bg;
	gameplay::SpriteBatch* tiling_bg;
public:
	/// Initialises this object.
	void Init();

	/// Sets a string to draw.
	/// @param	str	The.
	void SetStringToDraw(std::string str);

	/// Draw text.
	void Render();

	/// Called to see if
	/// @param	dt	The dt.
	void Update(float dt);
};

#endif  // __SELECTED_TEXT_LABEL__hpp
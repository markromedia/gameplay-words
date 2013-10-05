#ifndef __LETTER_MANAGER__hpp
#define __LETTER_MANAGER__hpp

#include <vector>
#include <queue>

#include "gameplay.h"
#include "../game/board/board.hpp"
#include "tile.hpp"
#include "../renderable_node_repository.hpp"
#include "../game/board/dice_manager.hpp"
#include "selected_text_label.hpp"
#include "../game/board/board_solver.hpp"
#include "score_controller.hpp"
#include "selected_text_connector.hpp"

class LetterController {
private:
	/// Default constructor.
	LetterController();

	/// @summary	The instance.
	static LetterController* instance;

	/// @summary	The tiles.
	std::vector<Tile*> tiles;

	/// @summary	The selected tiles
	std::vector<Tile*> selected_tiles;

	/// @summary	The tiles available for use
	std::queue<Tile*> available_tiles;

	/// Refill empty grid cells.
	void refillEmptyBoardCells();

	/// @summary	Number of moving tiles.
	int moving_tiles_count;

	/// @summary	Number of shrinking tiles.
	int shrinking_tiles_count;

	/// @summary	true to draw selected text.
	bool draw_selected_text;

	/// @summary	true to do check selected letters.
	bool do_check_selected_letters;

	/// @summary	The last known touch x / y.
	gameplay::Vector2 last_known_touch;

	/// Checks selected letters and responds appropriately.
	void checkSelectedLetters();

	/// Assign tile to cell.
	/// @param [in,out]	cell	If non-null, the cell.
	/// @param [in,out]	tile	If non-null, the tile.
	void assignTileToCell(BoardCell* cell, Tile* tile);
public:
	/// Callback, called when the tile movement complete.
	/// @param [in,out]	tile	If non-null, the tile.
	/// @param	is_starting 	true if this object is starting. false is stopping
	void TileMovementCompleteCallback(Tile* tile, bool is_starting);

	/// Callback, called when the tile shrinking is complete.
	/// @param [in,out]	tile	If non-null, the tile.
	/// @param	is_starting 	true if this object is starting. false is stopping
	void TileShrinkingCompleteCallback(Tile* tile, bool is_starting);

	/// Updates the given dt.
	/// @param	dt	The dt.
	void Update(float dt);

	/// Initialises this object.
	/// @param [in,out]	scene	If non-null, the scene.
	static void Init(gameplay::Scene* scene);

	/// Gets the singleton instance.
	/// @return	null if it fails, else.
	static LetterController* get();

	/// Creates a initial letter state
	static void InitializeLetters();

	/// Handles the touch down event.
	/// @param	ray the calculated ray
	/// @param	x	The x coordinate.
	/// @param	y	The y coordinate.
	/// @return	true if it succeeds, false if it fails.
	static bool HandleTouchDownEvent(gameplay::Ray& ray, int x, int y);

	/// Handles the touch up event.
	/// @param	x	The x coordinate.
	/// @param	y	The y coordinate.
	static void HandleTouchUpEvent(int x, int y);

	static void Render(gameplay::Camera* camera);
};


#endif  // __LETTER_MANAGER__hppr
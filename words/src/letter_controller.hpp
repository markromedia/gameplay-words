#ifndef __LETTER_MANAGER__hpp
#define __LETTER_MANAGER__hpp

#include <vector>
#include <queue>

#include "gameplay.h"
#include "tile.hpp"
#include "renderable_node_repository.hpp"
#include "letter_provider.hpp"
#include "selected_text_label.hpp"
#include "word_checker.hpp"

class Tile;
class GridColumn;

class GridCell {
public:
	GridColumn* parent_column;
	Tile* tile;
	int x;
	int y;
};

class GridColumn {
private:
	/// runs the adjustment algorithm recursively until 
	/// count is 0
	/// @param	count	the recursive counter
	void adjust(int count);
public:
	/// @summary	The cells of this grid.
	GridCell* cells[4];

	/// Adjusts this object.
	void AdjustTiles();
};

class Grid {
public:
	GridColumn* columns[4];

	/// Removes the given tile from its cell
	/// @param [in,out]	tile	If non-null, the Tile* to remove.
	void Remove(Tile* tile);

	/// Adjust the tiles to fill in spaces 
	void AdjustColumns();
};

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

	/// @summary	The 4x4 grid that positions the letters.
	Grid* grid;

	/// Builds the grid.
	/// @param [in,out]	letter_model	If non-null, the letter model.
	void buildGrid(gameplay::Node* letter_model);

	/// Refill empty grid cells.
	void refillEmptyGridCells();

	/// @summary	Number of moving tiles.
	int moving_tiles_count;

	/// @summary	The selected text label.
	SelectedTextLabel* selectedTextLabel;

	/// @summary	true to draw selected text.
	bool draw_selected_text;
public:
	/// Callback, called when the tile movement complete.
	/// @param [in,out]	tile	If non-null, the tile.
	/// @param	is_starting 	true if this object is starting. false is stopping
	void TileMovementCompleteCallback(Tile* tile, bool is_starting);

	/// Updates the given dt.
	/// @param	dt	The dt.
	void Update(float dt);

	/// Initialises this object.
	/// @param [in,out]	scene	If non-null, the scene.
	static void Init(gameplay::Scene* scene);

	/// Gets the singleton instance.
	/// @return	null if it fails, else.
	static LetterController* get();

	/// Handles the touch down event.
	/// @param	ray the calculated ray
	/// @param	x	The x coordinate.
	/// @param	y	The y coordinate.
	/// @return	true if it succeeds, false if it fails.
	static bool HandleTouchDownEvent(gameplay::Ray& ray, int x, int y);

	/// Handles the touch up event.
	static void HandleTouchUpEvent();

	static void Render(gameplay::Camera* camera);
};


#endif  // __LETTER_MANAGER__hppr
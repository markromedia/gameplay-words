#ifndef __LETTER_MANAGER__hpp
#define __LETTER_MANAGER__hpp

#include <vector>

#include "gameplay.h"
#include "tile.hpp"
#include "renderable_node_repository.hpp"
#include "letter_provider.hpp"

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

	/// @summary	The 4x4 grid that positions the letters.
	Grid* grid;

	/// @summary	The renderables.
	std::vector<Tile*> renderables;

	/// @summary	true if the tiles are growing.
	bool is_growing;

	/// Builds the grid.
	/// @param [in,out]	letter_model	If non-null, the letter model.
	void buildGrid(gameplay::Node* letter_model);
public:
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

	void Update(float dt);
};


#endif  // __LETTER_MANAGER__hppr
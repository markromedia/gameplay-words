#ifndef __TIME_TANK_CONTROLLER__hpp
#define __TIME_TANK_CONTROLLER__hpp

#include <vector>

#include "gameplay.h"

class BoardCell;
class BoardTile {
private:
public:
	BoardCell* cell;
	int row_index;
	int col_index;
	virtual void SetPosition(int x, int y, int z) = 0;
	virtual void TranslateTo(int x, int y, int z, float delay) = 0;
};
#endif  // __TIME_TANK_CONTROLLER__hpp
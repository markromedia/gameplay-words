#include "board.hpp"

#include "tile.hpp"

#ifdef WIN32
#include "../src-win/board_file_loader.hpp"
#elif __APPLE__
#include "../src-ios/board_file_loader.hpp"
#endif

Board* Board::instance = NULL;
long Board::start_time = 0;

void BoardCell::AssignTile( Tile* tile, bool assignPosition)
{
	if (tile == NULL) {
		this->tile = NULL;
		return;
	}
	this->tile = tile;
	tile->cell = this;
	tile->row_index = this->row_index;
	tile->col_index = this->col_index;
	if (assignPosition) {
		tile->SetPosition(x, y, 0);
	}
}

bool BoardCell::IsEmpty() {
	return this->tile == NULL;
}

void BoardColumn::adjust(int count) {
	//recursive end condition
	if (count == 0) {
		return;
	}

	BoardCell* first_empty = NULL;
	BoardCell* first_non_empty = NULL;

	//find first empty
	int non_empty_search_index = 0;
	for (int i = 0; i < 4; i++) {
		if (!first_empty && !cells[i]->tile) {
			first_empty = cells[i];
			non_empty_search_index = i;
		}
	}

	//find the first non-empty starting at the search index
	int idx_of_first_non_empty;
	for (int i = non_empty_search_index; i < 4; i++) {
		if (!first_non_empty && cells[i]->tile) {
			first_non_empty = cells[i];
			idx_of_first_non_empty = i;
		}
	}

	if (first_empty && first_non_empty) {
		//translate the non-empty to the empty position
		first_non_empty->tile->TranslateTo(first_empty->x, first_empty->y, 0, (idx_of_first_non_empty - 1) * 75);
		//update the empties now
		first_empty->AssignTile(first_non_empty->tile, false);
		first_non_empty->tile = NULL;
	}

	//recurse
	adjust(--count);
}

void BoardColumn::AdjustTiles()
{
	//check if any empties 
	int non_empty_count = 0;

	for (int i = 0; i < 4; i++) {
		if (cells[i]->tile) {
			non_empty_count++;
		}
	}
	//if we have no empties, no need to proceed
	if (non_empty_count == 4) {
		return;
	}

	adjust(non_empty_count);
}

BoardCell* &BoardColumn::operator[](int index) {
	return cells[index];
}

void Board::AdjustColumns()
{
	for (int i = 0; i < 4; i++) {
		BoardColumn* column = instance->columns[i];
		column->AdjustTiles();
	}
}

void Board::Remove( Tile* tile )
{
	for (int i = 0; i < 4; i++) {
		BoardColumn* column = instance->columns[i];
		for (int j = 0; j < 4; j++) {
			if (column->cells[j]->tile == tile) {
				column->cells[j]->tile = NULL;
				return;
			}
		}
	}
}

BoardColumn** Board::Columns()
{
	return instance->columns;
}

BoardColumn* &Board::operator [](int index) {
	return columns[index];
}

Board* Board::get()
{
	return instance;
}

void Board::Init(gameplay::Node* letter_model ) {
	instance = new Board();

	//position initial 16
	int row_count = 4;
	int col_count = 4;

	//the width and heigth of the mesh
	int letter_width = letter_model->getModel()->getMesh()->getBoundingBox().max.x - letter_model->getModel()->getMesh()->getBoundingBox().min.x;
	int letter_height = letter_model->getModel()->getMesh()->getBoundingBox().max.z - letter_model->getModel()->getMesh()->getBoundingBox().min.z;

	//the space between the letter
	int x_space = 0;
	int y_space = 0;

	int y_offset = 25;
	int start_x = (col_count * letter_width + (x_space * (col_count - 1))) / -2 + letter_width / 2;
	int start_y = (row_count * letter_height + (y_space * (row_count - 1))) / -2 + (letter_height / 2 + y_offset);

	for (int i = 0; i < col_count; i++) { //col
		BoardColumn* column = new BoardColumn();
		Board::Columns()[i] = column;

		for (int j = 0; j < row_count; j++) { //row
			BoardCell* cell = new BoardCell();
			cell->x = start_x + (i * (x_space + letter_width));
			cell->y = start_y + (j * (y_space + letter_height));
			cell->col_index = i;
			cell->row_index = j;

			column->cells[j] = cell;
		}
	}

	instance->buildPrecomputerBoardsQueue();
}


void Board::buildPrecomputerBoardsQueue()
{
#ifdef WIN32
	BoardFileLoader::LoadPrecalculatedBoard(&precalculated_boards);
#elif __APPLE__
    BoardFileLoader::LoadPrecalculatedBoard(&precalculated_boards);
#endif
}


void Board::PrepareBoard()
{
	start_time = gameplay::Game::getInstance()->getAbsoluteTime();
}

void Board::AssignBoard()
{
	for (int i = 0; i < 4; i++) {
		BoardColumn* column = Board::Columns()[i];
		for (int j = 0; j < 4; j++) {
			if (column->cells[j]->tile == NULL) {
				column->cells[j]->die = DiceManager::GetRandomDie();
			}
		}
	}
}

void Board::CreateNewBoardFromPrecalculatedBoards()
{
	PrecalculatedBoard* board = instance->precalculated_boards.front();
	instance->precalculated_boards.pop();
	DiceManager::ReassignDice();
	int index = 0;
	for (int row = 3; row >= 0; row--) {
		for (int col = 0; col < 4; col++) {
			BoardColumn* column = Board::Columns()[col];
			BoardCell* cell = column->cells[row];
			cell->die = DiceManager::GetDieById(board->board[index][0]);
			cell->die->side_index = board->board[index][1];
			index++;
		}
	}
	//remove the board from mem
	delete board;
}

void Board::CreateRandomBoard() {
	DiceManager::ReassignDice();
	for (int row = 3; row >= 0; row--) {
		for (int col = 0; col < 4; col++) {
			BoardColumn* column = Board::Columns()[col];
			BoardCell* cell = column->cells[row];
			cell->die = DiceManager::GetRandomDie();
		}
	}
}

void Board::PrintBoard() {
	gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, "\n");
	for (int row = 3; row >= 0; row--) {
		for (int col = 0; col < 4; col++) {
			BoardColumn* column = Board::Columns()[col];
			BoardCell* cell = column->cells[row];
			
			gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, cell->die->getAssignedLetter().c_str());
			gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, " ");
		}
		gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, "\n");
	}
}





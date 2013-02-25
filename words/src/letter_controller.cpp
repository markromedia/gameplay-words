#include "letter_controller.hpp"

LetterController* LetterController::instance = NULL;

///-----------------------------------------------------------------------------------------------

void GridColumn::adjust(int count) {
	//recursive end condition
	if (count == 0) {
		return;
	}

	GridCell* first_empty = NULL;
	GridCell* first_non_empty = NULL;

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
		first_empty->tile = first_non_empty->tile;
		first_non_empty->tile = NULL;
	}

	//recurse
	adjust(--count);
}

void GridColumn::AdjustTiles()
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

void Grid::AdjustColumns()
{
	for (int i = 0; i < 4; i++) {
		GridColumn* column = columns[i];
		column->AdjustTiles();
	}
}

void Grid::Remove( Tile* tile )
{
	for (int i = 0; i < 4; i++) {
		GridColumn* column = columns[i];
		for (int j = 0; j < 4; j++) {
			if (column->cells[j]->tile == tile) {
				column->cells[j]->tile = NULL;
				return;
			}
		}
	}
}

///-----------------------------------------------------------------------------------------------

LetterController::LetterController()
{
	tiles.reserve(16);
	grid = new Grid();
	moving_tiles_count = 0;
}

void LetterController::buildGrid( gameplay::Node* letter_model )
{
	//position initial 16
	int row_count = 4;
	int col_count = 4;

	//the width and heigth of the mesh
	int letter_width = letter_model->getModel()->getMesh()->getBoundingBox().max.x - letter_model->getModel()->getMesh()->getBoundingBox().min.x;
	int letter_height = letter_model->getModel()->getMesh()->getBoundingBox().max.z - letter_model->getModel()->getMesh()->getBoundingBox().min.z;

	//the space between the letter
	int x_space = 0;
	int y_space = 0;

	int start_x = (col_count * letter_width + (x_space * (col_count - 1))) / -2 + letter_width / 2;
	int start_y = (row_count * letter_height + (y_space * (row_count - 1))) / -2 + (letter_height / 2 + 20);

	for (int i = 0; i < col_count; i++) { //col
		GridColumn* column = new GridColumn();
		grid->columns[i] = column;

		for (int j = 0; j < row_count; j++) { //row
			GridCell* cell = new GridCell();
			cell->x = start_x + (i * (x_space + letter_width));
			cell->y = start_y + (j * (y_space + letter_height));

			column->cells[j] = cell;
		}
	}
}

void LetterController::refillEmptyGridCells()
{
	for (int i = 0; i < 4; i++) {
		GridColumn* column = grid->columns[i];
		for (int j = 0; j < 4; j++) {
			if (column->cells[j]->tile == NULL) {
				if (available_tiles.empty()) {
					return;
				}

				//grab a tile from the available tiles
				Tile* tile = available_tiles.front();
				available_tiles.pop();

				//assign grid values and tie it to the cell
				column->cells[j]->tile = tile;
				tile->is_visible = true;
				tile->SetPosition(column->cells[j]->x, column->cells[j]->y, 0);

				//assign a new letter
				std::string letter_material = "letter_";
				letter_material.append(LetterProvider::getNextLetter(i));
				tile->GetLayer(Tile::ICON)->SetRenderableNode(RENDERABLE(letter_material));

				//start the tile popping
				tile->PlayPopAnimation();
			}
		}
	}
}

void LetterController::Init(gameplay::Scene* scene)
{
	instance = new LetterController();

	//the model we'll use for the physics stuff
	gameplay::Node* letter_model = scene->findNode("letter_tile");

	//build the grid
	instance->buildGrid(letter_model);
	
	//the physics params of each letter
	gameplay::PhysicsRigidBody::Parameters params;
	params.mass = 10.0f;

	//create the tiles
	for (unsigned int i = 0; i < instance->tiles.capacity(); i++) {
		//create an init the node we'll use for physics
		gameplay::Node* physics_node = letter_model->clone();
		physics_node->setCollisionObject(gameplay::PhysicsCollisionObject::RIGID_BODY, gameplay::PhysicsCollisionShape::box(), &params);
		scene->addNode(physics_node);

		Tile* tile = new Tile(physics_node, instance);
		//add ref to the tile
		physics_node->setUserPointer(tile);

		//create the layers 
		tile->CreateLayer(Tile::BASE, scene);
		tile->CreateLayer(Tile::ICON, scene);

		instance->tiles.push_back(tile);
	}

	//position tile and init letter
	Grid* grid = instance->grid;
	for (int i = 0; i < 4; i++) {
		GridColumn* column = grid->columns[i];
		for (int j = 0; j < 4; j++) {
			Tile* tile = instance->tiles[i * 4 + j];
			GridCell* cell = column->cells[j];

			cell->tile = tile;

			tile->SetPosition(cell->x, cell->y, 0);
			tile->GetLayer(Tile::BASE)->SetRenderableNode(RENDERABLE("letter_layer_unselected_background"));

			//assign a letter
			std::string letter_material = "letter_";
			letter_material.append(LetterProvider::getNextLetter(i));
			tile->GetLayer(Tile::ICON)->SetRenderableNode(RENDERABLE(letter_material));

			instance->tiles.push_back(tile);
		}
	}
}

bool LetterController::HandleTouchDownEvent(gameplay::Ray& ray, int x, int y )
{
	//check all the registered tiles to see if they intersect
	for(std::vector<Tile*>::iterator it = instance->tiles.begin(); it != instance->tiles.end(); ++it) {			
		Tile* tile = *it;
		if (tile->is_visible && tile->Intersects(ray)) {
			//add to list of tiles if not already there
			if (!tile->is_selected) {
				instance->selected_tiles.push_back(tile);
			}
			tile->is_selected = true;
			return true;
		}
	}

	return false;
}

void LetterController::HandleTouchUpEvent()
{
	//remove the selected tiles
	for(std::vector<Tile*>::iterator it = instance->selected_tiles.begin(); it != instance->selected_tiles.end(); ++it) {			
		Tile* tile = *it;
		tile->is_visible = false;
		//add this tile to the available list
		instance->available_tiles.push(tile);
		//find this tile and remove it from the grid
		instance->grid->Remove(tile);
	}

	//clear selected list
	instance->selected_tiles.clear();

	//adjust the grid
	instance->grid->AdjustColumns();

	//check the movement count. if the movement count is 0 after adjustment, means no movement, 
	//but there are still empties. need to force the pop now
	if (instance->moving_tiles_count == 0) {
		instance->refillEmptyGridCells();
	}

	for(std::vector<Tile*>::iterator it = instance->tiles.begin(); it != instance->tiles.end(); ++it) {			
		Tile* tile = *it;
		tile->is_selected = false;
	}
}

void LetterController::Render(gameplay::Camera* camera)
{
	for(std::vector<Tile*>::iterator it = instance->tiles.begin(); it != instance->tiles.end(); ++it) {			
		Tile* tile = *it;
		if (tile->is_selected) {
			tile->GetLayer(Tile::BASE)->SetRenderableNode(RENDERABLE("letter_layer_selected_background"));
		} else {
			tile->GetLayer(Tile::BASE)->SetRenderableNode(RENDERABLE("letter_layer_unselected_background"));

		}

		if (tile->is_visible) {
			tile->Render(camera);
		}
	}
}

void LetterController::Update( float dt )
{
	for(std::vector<Tile*>::iterator it = instance->tiles.begin(); it != instance->tiles.end(); ++it) {			
		Tile* tile = *it;
		tile->Update(dt);
	}
}

LetterController* LetterController::get()
{
	return instance;
}

void LetterController::TileMovementCompleteCallback( Tile* tile, bool is_starting )
{
	if (is_starting) {
		moving_tiles_count++;
	} else {
		moving_tiles_count--;
	}

	//if we're at 0, means everyone is done and time to refill the empty spaces
	if (moving_tiles_count == 0) {
		refillEmptyGridCells();
	}
}

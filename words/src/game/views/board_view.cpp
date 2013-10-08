#include "board_view.hpp"

#include "tile.hpp"

BoardView* BoardView::instance = NULL;

BoardView::BoardView()
{
	tiles.reserve(16);
	moving_tiles_count = 0;
	shrinking_tiles_count = 0;
	draw_selected_text = false;
}

void BoardView::Init(gameplay::Scene* scene)
{
	instance = new BoardView();

	//the model we'll use for the physics stuff
	gameplay::Node* letter_model = scene->findNode("letter_tile");

	//the physics params of each letter
	gameplay::PhysicsRigidBody::Parameters params;
	params.mass = 10.0f;

	//create the tiles
	for (unsigned int i = 0; i < instance->tiles.capacity(); i++) {
		//create an init the node we'll use for physics
		gameplay::Node* physics_node = letter_model->clone();
		physics_node->setCollisionObject(gameplay::PhysicsCollisionObject::RIGID_BODY, gameplay::PhysicsCollisionShape::box(), &params);
		scene->addNode(physics_node);

		Tile* tile = new Tile(physics_node);
		//add ref to the tile
		physics_node->setUserPointer(tile);

		//create the layers 
		tile->CreateLayer(Tile::BASE, scene);
		tile->CreateLayer(Tile::ICON, scene);
		tile->CreateLayer(Tile::SCORE, scene);

		instance->tiles.push_back(tile);
	}
}

void BoardView::assignTileToCell( BoardCell* cell, Tile* tile )
{
	//assign grid values and tie it to the cell
	cell->AssignTile(tile, true);

	//assign a new letter
	std::string letter_material = "letter_";
	letter_material.append(cell->die->getAssignedLetter());
	tile->value = cell->die->getAssignedLetter();
	//assign rendenderables
	tile->GetLayer(Tile::ICON)->SetRenderableNode(RENDERABLE(letter_material));
	ScoreView::AssignScoreLayer(tile);
}

void BoardView::refillEmptyBoardCells()
{
	//tell board to assign its letters
	Board::AssignBoard();

	//iterate over board and reassign non-empties
	for (int i = 0; i < 4; i++) {
		BoardColumn* column = Board::Columns()[i];
		for (int j = 0; j < 4; j++) {
            BoardCell* cell = column->cells[j];
			if (cell->IsEmpty() && !available_tiles.empty()) {
				//grab a tile from the available tiles
				Tile* tile = available_tiles.front();
				available_tiles.pop();

				//assign to the tile to the cell
				assignTileToCell(cell, tile);

				//start the tile popping
				tile->PlayPopAnimation();
			}
		}
	}
}

void BoardView::InitializeLetters()
{
	//Tell the board to create a new board
	Board::CreateNewBoardFromPrecalculatedBoards();

	//position tile and init letter
	for (int row = 3; row >= 0; row--) {
		for (int col = 0; col < 4; col++) {
			Tile* tile = instance->tiles[row * 4 + col];
			BoardColumn* column = Board::Columns()[col];
			BoardCell* cell = column->cells[row];
			
			//assign tile to cell
			instance->assignTileToCell(cell, tile);

			//set background
			tile->GetLayer(Tile::BASE)->SetRenderableNode(RENDERABLE("letter_layer_unselected_background"));
		}
	}
}

bool BoardView::HandleTouchDownEvent(gameplay::Ray& ray, int x, int y )
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

void BoardView::HandleTouchUpEvent(int x, int y)
{
	instance->do_check_selected_letters = true;
	instance->last_known_touch.x = x;
	instance->last_known_touch.y = y;
}

void BoardView::checkSelectedLetters() {
	if (instance->selected_tiles.size() == 0) {
		return;
	}

	//construct the word and check it
	std::string selected_text = "";
	for(std::vector<Tile*>::iterator it = instance->selected_tiles.begin(); it != instance->selected_tiles.end(); ++it) {			
		Tile* tile = *it;
		if (tile->value.length() > 0)
			selected_text.append(tile->value);	
	}

	if (selected_text.length() > 1 && BoardSolver::IsWord(selected_text.c_str())) {
		//add to the points
		ScoreView::AddToScore(selected_tiles, &last_known_touch);
        
        //remove the selected tiles
		for(std::vector<Tile*>::iterator it = instance->selected_tiles.begin(); it != instance->selected_tiles.end(); ++it) {
			Tile* tile = *it;
            //find this tile and remove it from the grid and clean up the cell it belonged to
			Board::RemoveTileAndCleanupCell(tile);
			//add this tile to the available list
			instance->available_tiles.push(tile);
        }

		//drop the tiles into the new locations that will be made available when the
		//used letters collapse. This doesn't trigger the actual translation yet, but
		//simply moves the tile/die associations
		Board::DropTiles();

		//tell the board to start solving itself to figure out whats the 
		//best combination of dice to add to the board
		Board::StartSolvingNewBoard();
        
        //tell all the tiles to shrink themselves
        for(std::vector<Tile*>::iterator it = instance->selected_tiles.begin(); it != instance->selected_tiles.end(); ++it) {
            Tile* tile = *it;
            //tell the tile to shrink itself (which will then kick off translation animation and finally popping animation)
            tile->PlayShrinkingAnimation();
        }
	}
    
	//make sure everything is unselected
	for(std::vector<Tile*>::iterator it = instance->tiles.begin(); it != instance->tiles.end(); ++it) {			
		Tile* tile = *it;
		tile->is_selected = false;
	}

	//clear selected list
	instance->selected_tiles.clear();
}

void BoardView::Render(gameplay::Camera* camera)
{
	SelectedTextConnector::Draw(instance->selected_tiles);
	for(std::vector<Tile*>::iterator it = instance->tiles.begin(); it != instance->tiles.end(); ++it) {			
		Tile* tile = *it;
		if (tile->is_selected) {
			tile->GetLayer(Tile::BASE)->SetRenderableNode(RENDERABLE("letter_layer_selected_background"));
		} else {
			tile->GetLayer(Tile::BASE)->SetRenderableNode(RENDERABLE("letter_layer_unselected_background"));

		}

		if (tile->is_visible) {
			tile->Render();
		}
	}
}

void BoardView::Update( float dt )
{
	if (do_check_selected_letters) {
		instance->checkSelectedLetters();
		do_check_selected_letters = false;
	}

	//draw the selected text if there are any characters
	if (instance->selected_tiles.size() > 0) {
		std::string selected_text = "";
		for(std::vector<Tile*>::iterator it = instance->selected_tiles.begin(); it != instance->selected_tiles.end(); ++it) {			
			Tile* tile = *it;
			if (tile->value.length() > 0)
				selected_text.append(tile->value);	
		}
		SelectedTextLabel::get()->SetStringToDraw(selected_text);
	}

	for(std::vector<Tile*>::iterator it = instance->tiles.begin(); it != instance->tiles.end(); ++it) {			
		Tile* tile = *it;
		tile->Update(dt);
	}
}

BoardView* BoardView::get()
{
	return instance;
}

void BoardView::TileMovementCompleteCallback( Tile* tile, bool is_starting )
{
	if (is_starting) {
		moving_tiles_count++;
	} else {
		moving_tiles_count--;
	}

	//if we're at 0, means everyone is done and time to refill the empty spaces
	if (moving_tiles_count == 0) {
		refillEmptyBoardCells();
	}
}

void BoardView::TileShrinkingCompleteCallback( Tile* tile, bool is_starting )
{
	if (is_starting) {
		shrinking_tiles_count++;
	} else {
		shrinking_tiles_count--;
	}
	
	if (shrinking_tiles_count == 0) {
		//move any tiles which were marked as needing a tran
		for(std::vector<Tile*>::iterator it = instance->tiles.begin(); it != instance->tiles.end(); ++it) {			
			(*it)->ApplyTranslation();
		}

		//check the movement count. if the movement count is 0 after adjustment, means no movement, 
		//but there are still empties. need to force the pop now
		if (instance->moving_tiles_count == 0) {
			instance->refillEmptyBoardCells();
		}
	}
}

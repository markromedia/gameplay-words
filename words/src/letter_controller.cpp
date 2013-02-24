#include "letter_controller.hpp"

LetterController* LetterController::instance = NULL;

LetterController::LetterController()
{
	tiles.reserve(26);
	renderables.reserve(26);
}

void LetterController::Init(gameplay::Scene* scene)
{
	instance = new LetterController();

	//the model we'll use for the physics stuff
	gameplay::Node* letter_model = scene->findNode("letter_tile");
	
	//the physics params of each letter
	gameplay::PhysicsRigidBody::Parameters params;
	params.mass = 10.0f;

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

		instance->tiles.push_back(tile);
	}

	//position initial 16
	int row_count = 4;
	int col_count = 4;

	//the width and heigth of the mesh
	int letter_width = letter_model->getModel()->getMesh()->getBoundingBox().max.x - letter_model->getModel()->getMesh()->getBoundingBox().min.x;
	int letter_height = letter_model->getModel()->getMesh()->getBoundingBox().max.z - letter_model->getModel()->getMesh()->getBoundingBox().min.z;
	
	//the space between the letter
	int x_space = 0;
	int y_space = 0;
	
	int start_x = (col_count * letter_width + (x_space * (col_count - 1))) / -2;
	int start_y = (row_count * letter_height + (y_space * (row_count - 1))) / -2;

	int x_offset = letter_width / 2;
	int y_offset = letter_height / 2 + 20;


	for (int i = 0; i < row_count; i++) { //row
		for (int j = 0; j < col_count; j++) { //col
			Tile* tile = instance->tiles[(i * row_count) + j];
			
			int x = start_x + (j * (x_space + letter_width));
			int y = start_y + (i * (y_space + letter_height));

			tile->SetPosition(x + x_offset, y + y_offset, 0);
			tile->GetLayer(Tile::BASE)->SetRenderableNode(RENDERABLE("letter_layer_unselected_background"));

			//assign a letter
			std::string letter_material = "letter_";
			letter_material.append(LetterProvider::getNextLetter(i));
			tile->GetLayer(Tile::ICON)->SetRenderableNode(RENDERABLE(letter_material));

			instance->renderables.push_back(tile);
		}
	}
}

bool LetterController::HandleTouchDownEvent(gameplay::Ray& ray, int x, int y )
{
	//check all the registered tiles to see if they intersect
	for(std::vector<Tile*>::iterator it = instance->tiles.begin(); it != instance->tiles.end(); ++it) {			
		Tile* tile = *it;
		if (tile->Intersects(ray)) {
			tile->GetLayer(Tile::BASE)->SetRenderableNode(RENDERABLE("letter_layer_selected_background"));
			return true;
		}
	}

	return false;
}

void LetterController::HandleTouchUpEvent()
{
	for(std::vector<Tile*>::iterator it = instance->tiles.begin(); it != instance->tiles.end(); ++it) {			
		Tile* tile = *it;
		tile->GetLayer(Tile::BASE)->SetRenderableNode(RENDERABLE("letter_layer_unselected_background"));
	}
}

void LetterController::Render(gameplay::Camera* camera)
{
	for(std::vector<Tile*>::iterator it = instance->renderables.begin(); it != instance->renderables.end(); ++it) {			
		Tile* tile = *it;
		tile->Render(camera);
	}
}

void LetterController::Update( float dt )
{

}

LetterController* LetterController::get()
{
	return instance;
}



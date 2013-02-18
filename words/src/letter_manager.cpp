#include "letter_manager.hpp"

LetterManager* LetterManager::instance = NULL;

LetterManager::LetterManager()
{
	tiles.reserve(26);
	renderables.reserve(26);
}

void LetterManager::Init(gameplay::Scene* scene)
{
	instance = new LetterManager();
	
	for (unsigned int i = 0; i < instance->tiles.capacity(); i++) {
		Tile* tile = new Tile();
		//create the layers 
		tile->CreateLayer(Tile::BASE, scene);
		//tile->CreateLayer(Tile::ICON, scene, source_node->clone());

		instance->tiles.push_back(tile);
	}

	//position initial 16
	int row_count = 4;
	int col_count = 4;
	for (int i = 0; i < row_count; i++) { //row
		for (int j = 0; j < col_count; j++) { //col
			Tile* tile = instance->tiles[(i * row_count) + j];
			
			int x = -90 + (j * 45);
			int y = -90 + (i * 45);

			tile->SetPosition(x, y, 0);
			tile->GetLayer(Tile::BASE)->SetRenderableNode(RENDERABLE("letter_layer_unselected_background"));

			instance->renderables.push_back(tile);
		}
	}

	instance->tiles[3]->CreateLayer(Tile::ICON, scene, RENDERABLE("powerup_arrows"));
}

void LetterManager::Render(gameplay::Camera* camera)
{
	for(std::vector<Tile*>::iterator it = instance->renderables.begin(); it != instance->renderables.end(); ++it) {			
		Tile* tile = *it;
		tile->Render(camera);
	}
}

void LetterManager::Update( float dt )
{

}

LetterManager* LetterManager::get()
{
	return instance;
}



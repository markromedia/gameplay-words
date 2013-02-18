#include "renderable_node_repository.hpp"

RenderableNodeRepository* RenderableNodeRepository::instance = NULL;

void RenderableNodeRepository::Init(gameplay::Scene * scene) {
	RenderableNodeRepository::instance = new RenderableNodeRepository;

	//grab the models in the scene we're copying
	gameplay::Node* letter_model = scene->findNode("letter_tile");
	gameplay::Node* powerup_model = scene->findNode("powerup");

	//init the letter background
	instance->initializeNode("letter_layer_unselected_background","res/words.material#letter", letter_model->clone(), scene);

	//init the powerups
	instance->initializeNode("powerup_arrows","res/words.material#powerup_arrows", letter_model->clone(), scene);

	
	//init the letters
	
	
}

void RenderableNodeRepository::initializeNode(const char* id, const char* material_id, gameplay::Node* model_node, gameplay::Scene* scene) {
	gameplay::Material* material = gameplay::Material::create(material_id);
	model_node->getModel()->setMaterial(material);

	scene->addNode(model_node);
	renderable_node_map[id] = model_node;

	//they're all clones, so release is ok
	model_node->release();
}

RenderableNodeRepository* RenderableNodeRepository::get() {
	return instance;
}

RenderableNodeRepository& RenderableNodeRepository::_() {
	return *instance;
}

gameplay::Node* RenderableNodeRepository::getRenderableNode(const char* id) {
	return renderable_node_map[id];
}

gameplay::Node* &RenderableNodeRepository::operator [](const char* id) {
	return renderable_node_map[id];
}
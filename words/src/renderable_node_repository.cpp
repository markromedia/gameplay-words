#include "renderable_node_repository.hpp"

RenderableNodeRepository* RenderableNodeRepository::instance = NULL;

void RenderableNodeRepository::Init(gameplay::Scene * scene) {
	RenderableNodeRepository::instance = new RenderableNodeRepository;

	//grab the models in the scene we're copying
	gameplay::Node* letter_model = scene->findNode("letter_tile");
	gameplay::Node* powerup_model = scene->findNode("powerup");

	//init the letter background
	instance->initializeNode("letter_layer_unselected_background","res/words.material#letter_layer_unselected_background", letter_model->clone(), scene);

	//init the selected letter background
	instance->initializeNode("letter_layer_selected_background","res/words.material#letter_layer_selected_background", letter_model->clone(), scene);

	//init the powerups
	instance->initializeNode("powerup_arrows","res/words.material#powerup_arrows", letter_model->clone(), scene);

	//init the letters
	instance->initializeNode("letter_a","res/words.material#letter_a", letter_model->clone(), scene);
	instance->initializeNode("letter_b","res/words.material#letter_b", letter_model->clone(), scene);
	instance->initializeNode("letter_c","res/words.material#letter_c", letter_model->clone(), scene);
	instance->initializeNode("letter_d","res/words.material#letter_d", letter_model->clone(), scene);
	instance->initializeNode("letter_e","res/words.material#letter_e", letter_model->clone(), scene);
	instance->initializeNode("letter_f","res/words.material#letter_f", letter_model->clone(), scene);
	instance->initializeNode("letter_g","res/words.material#letter_g", letter_model->clone(), scene);
	instance->initializeNode("letter_h","res/words.material#letter_h", letter_model->clone(), scene);
	instance->initializeNode("letter_i","res/words.material#letter_i", letter_model->clone(), scene);
	instance->initializeNode("letter_j","res/words.material#letter_j", letter_model->clone(), scene);
	instance->initializeNode("letter_k","res/words.material#letter_k", letter_model->clone(), scene);
	instance->initializeNode("letter_l","res/words.material#letter_l", letter_model->clone(), scene);
	instance->initializeNode("letter_m","res/words.material#letter_m", letter_model->clone(), scene);
	instance->initializeNode("letter_n","res/words.material#letter_n", letter_model->clone(), scene);
	instance->initializeNode("letter_o","res/words.material#letter_o", letter_model->clone(), scene);
	instance->initializeNode("letter_p","res/words.material#letter_p", letter_model->clone(), scene);
	instance->initializeNode("letter_qu","res/words.material#letter_qu", letter_model->clone(), scene);
	instance->initializeNode("letter_r","res/words.material#letter_r", letter_model->clone(), scene);
	instance->initializeNode("letter_s","res/words.material#letter_s", letter_model->clone(), scene);
	instance->initializeNode("letter_t","res/words.material#letter_t", letter_model->clone(), scene);
	instance->initializeNode("letter_u","res/words.material#letter_u", letter_model->clone(), scene);
	instance->initializeNode("letter_v","res/words.material#letter_v", letter_model->clone(), scene);
	instance->initializeNode("letter_w","res/words.material#letter_w", letter_model->clone(), scene);
	instance->initializeNode("letter_x","res/words.material#letter_x", letter_model->clone(), scene);
	instance->initializeNode("letter_y","res/words.material#letter_y", letter_model->clone(), scene);
	instance->initializeNode("letter_z","res/words.material#letter_z", letter_model->clone(), scene);
}

void RenderableNodeRepository::initializeNode(std::string id, const char* material_id, gameplay::Node* model_node, gameplay::Scene* scene) {
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

gameplay::Node* RenderableNodeRepository::getRenderableNode(std::string id) {
	return renderable_node_map[id];
}

gameplay::Node* &RenderableNodeRepository::operator [](std::string id) {
	return renderable_node_map[id];
}
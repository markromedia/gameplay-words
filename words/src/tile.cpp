#include "tile.hpp"

///-----------------------------------------------------------------------------------------------

TileLayer::TileLayer() {
	this->node = gameplay::Node::create();
}

void TileLayer::SetMaterial(gameplay::Material* material) {
	this->node->getModel()->setMaterial(material);
}

///-----------------------------------------------------------------------------------------------

Tile::Tile() {
	layers.reserve(8);
}

void Tile::CreateBaseLayer(gameplay::Scene* scene, gameplay::Model* model) {
	base_layer = new TileLayer();
	base_layer->node->setModel(model);
	layers.push_back(base_layer);
	scene->addNode(base_layer->node);
}

void Tile::CreateIconLayer(gameplay::Scene* scene, gameplay::Model* letter_model) {
	icon_layer = new TileLayer();
	icon_layer->node->setModel(letter_model);
	layers.push_back(icon_layer);
	scene->addNode(icon_layer->node);
}

void Tile::Update(gameplay::Scene* scene, float dt) {
	//figure out the billboarded orientation
	gameplay::Matrix m;
	gameplay::Matrix::createBillboard(position, scene->getActiveCamera()->getNode()->getTranslationWorld(), scene->getActiveCamera()->getNode()->getUpVectorWorld(), &m);
	gameplay::Quaternion q;
	m.getRotation(&q);

	for(std::vector<TileLayer*>::iterator it = layers.begin(); it != layers.end(); ++it) {
		(*it)->node->setTranslation(position.x, position.y, position.z);
		(*it)->node->setRotation(q);
	}
}

void Tile::Render() {
	for(std::vector<TileLayer*>::iterator it = layers.begin(); it != layers.end(); ++it) {
		(*it)->node->getModel()->draw();
	}
}
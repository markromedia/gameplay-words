#include "tile.hpp"

///-----------------------------------------------------------------------------------------------

TileLayer::TileLayer() {
}

void TileLayer::SetRenderableNode(gameplay::Node* renderable_node) {
	this->renderable_node = renderable_node;
}

///-----------------------------------------------------------------------------------------------

Tile::Tile() {
	layers.reserve(8);
}

void Tile::CreateLayer(LayerLevel layerLevel, gameplay::Scene* scene, gameplay::Node* node) {
	TileLayer* layer = new TileLayer();
	layer->renderable_node = node;
	layers.insert(layers.begin() + layerLevel, layer);
}

TileLayer* Tile::GetLayer(LayerLevel layerLevel) {
	return layers[layerLevel];
}

void Tile::Update(float dt) {
}

void Tile::SetPosition(int x, int y, int z) {
	position.x = x;
	position.y = y;
	position.z = z;
}

void Tile::Render(gameplay::Camera* camera) {
	//just in case
	if (layers.size() == 0) {
		return;
	}

	//update the first nodes position so we can use it to figure out the billboard transformation
	//layers[0]->renderable_node->setTranslation(position.x, position.y, position.z);


	/************************************************************************/
	/* NONE OF THIS STUFF IS USED                                           */
	/************************************************************************/
	//figure out the billboarded orientation
	gameplay::Quaternion q, p;
	gameplay::Matrix m, m2;

	gameplay::Matrix::createBillboard(layers[0]->renderable_node->getTranslationWorld(), camera->getNode()->getTranslationWorld(), camera->getNode()->getUpVectorWorld(), &m);

	//the models from 3ds are coming in with z facing up, so need to retain that original orientation
	m2.rotateX(90 * (MATH_PI / 180));
	m2.getRotation(&p);

	//get the billboard quaternion
	m.getRotation(&q);

	//premultiply our 90 degree x-axis rotation
	gameplay::Quaternion::multiply(q, p, &q);
	/************************************************************************/
	/* NONE OF THIS STUFF IS USED                                           */
	/************************************************************************/

	for(std::vector<TileLayer*>::iterator it = layers.begin(); it != layers.end(); ++it) {
		//update the renderable node and draw it where we need to
		(*it)->renderable_node->setTranslation(position.x, position.y, position.z);
		(*it)->renderable_node->setRotation(p);
		
		(*it)->renderable_node->getModel()->draw();
	}
}
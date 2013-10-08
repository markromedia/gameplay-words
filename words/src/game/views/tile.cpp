#include "tile.hpp"

#include "gameplay.h"

#include "../../camera_control.hpp"

#include "board_view.hpp"

using namespace gameplay;

///-----------------------------------------------------------------------------------------------

TileLayer::TileLayer() {
}

void TileLayer::SetRenderableNode(gameplay::Node* renderable_node) {
	this->renderable_node = renderable_node;
}

///-----------------------------------------------------------------------------------------------

Tile::Tile(gameplay::Node* physics_node) {
	this->physics_node = physics_node;

	layers.reserve(8);
	scale = 1.0f;
	is_visible = true;
	is_selected = false;
	animation = NONE;
	physics_node_scale = 0.75f;
	translation_is_dirty = false;
}

gameplay::Quaternion Tile::getBillboardTransformation() {
	//update the first nodes position so we can use it to figure out the billboard transformation
	physics_node->setTranslation(position.x, position.y, position.z);

	gameplay::Quaternion q, p;
	gameplay::Matrix m, m2;

	CameraControl::CreateBillboardHelper(physics_node->getTranslationWorld(), &m);

	//the models from 3ds are coming in with z facing up, so need to retain that original orientation
	m2.rotateX(90 * (MATH_PI / 180));
	m2.getRotation(&p);

	//get the billboard quaternion
	m.getRotation(&q);

	//premultiply our 90 degree x-axis rotation
	gameplay::Quaternion::multiply(q, p, &q);

	return q;
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
	switch (animation) {
	case DELAYING_TO_MOVE : {
		move_delay -= dt;
		if (move_delay <= 0) 
			animation = MOVING;
		break;
	}
	case MOVING : {
		position += (target_position - position) * (dt / (dt + 64));
		//we're only moving down, so we can rely on y to see if we've arrived
		if ((position.y - 0.5f) <= target_position.y) {
			position.y = target_position.y;
			move_delay = 0;
			animation = NONE;
			BoardView::get()->TileMovementCompleteCallback(this, false);
		}
		break;
	}
	case POPPING : {
		gameplay::MathUtil::smooth(&scale, 1.25f, dt, 32);
		if (scale >= 1.24f) {
			scale = 1.25f;
			animation = POPPING_SNAP_BACK;
		}
		break;
	}
	case POPPING_SNAP_BACK : {
		gameplay::MathUtil::smooth(&scale, 1, dt, 32);
		if (scale <= 1.1) {
			scale = 1.0;
			animation = NONE;
		}
		break;
	}
	case SHRINKING : {
		gameplay::MathUtil::smooth(&scale, 0.65f, dt, 16);//16);
		if (scale <= 0.66) {
			scale = 1.0f;
			is_visible = false;
			this->is_selected = false;
			animation = NONE;
			//tell controller we're done shrinking
			BoardView::get()->TileShrinkingCompleteCallback(this, false);
		}
		break;
	}
	}
}

void Tile::SetPosition(int x, int y, int z) {
	position.x = x;
	position.y = y;
	position.z = z;
}


void Tile::TranslateTo( int x, int y, int z, float delay)
{
	target_position.x = x;
	target_position.y = y;
	target_position.z = z;
	move_delay = delay;
	translation_is_dirty = true;

}

void Tile::ApplyTranslation()
{
	if (!translation_is_dirty) {
		return;
	}

	translation_is_dirty = false;

	if (animation == NONE) {
		//notified that will start to move
		BoardView::get()->TileMovementCompleteCallback(this, true);
	}

	//if not currently moving or getting ready to move, set the delay
	if (!(animation == DELAYING_TO_MOVE || animation == MOVING)) {
		animation = DELAYING_TO_MOVE;
	} 
}


void Tile::PlayPopAnimation()
{
	is_visible = true;
	animation = POPPING;
	scale = 0.3f;
}

void Tile::PlayShrinkingAnimation()
{
	//set it to selected, since this might reset
	this->is_selected = true;
	//we're staring to shrink, so tell controller
	BoardView::get()->TileShrinkingCompleteCallback(this, true);

	is_visible = true;
	animation = SHRINKING;
	scale = 1.2f;
}


void Tile::Render() {
	gameplay::Quaternion p;
	gameplay::Matrix m;

	m.rotateX(90 * (MATH_PI / 180));
	m.getRotation(&p);

	p = getBillboardTransformation();

	//make sure the physics node is also where it needs to be
	int physics_node_height = physics_node->getModel()->getMesh()->getBoundingBox().max.z - physics_node->getModel()->getMesh()->getBoundingBox().min.z;
	physics_node->setTranslation(position.x, position.y  - ((1 - physics_node_scale) * (physics_node_height / 2)), position.z);
	physics_node->setRotation(p);
	physics_node->setScale(physics_node_scale);

	for(unsigned int i = 0; i < layers.size(); i++) {
		TileLayer* tileLayer = layers[i];
		if (tileLayer && tileLayer->renderable_node) {
			//figure out y based on scale
			int height = tileLayer->renderable_node->getModel()->getMesh()->getBoundingBox().max.z - tileLayer->renderable_node->getModel()->getMesh()->getBoundingBox().min.z;
			float y = position.y - ((1 - scale) * height / 2);

			//update the renderable node and draw it where we need to
			tileLayer->renderable_node->setTranslation(position.x, y, position.z);
			tileLayer->renderable_node->setRotation(p);
			tileLayer->renderable_node->setScale(scale);

			tileLayer->renderable_node->getModel()->draw();
		}
	}
}

bool Tile::Intersects( gameplay::Ray& ray )
{
	if (physics_node) {
		gameplay::BoundingBox bbox = physics_node->getModel()->getMesh()->getBoundingBox();
		bbox.transform(physics_node->getWorldMatrix());
		float distance = ray.intersects(bbox);
		if (distance != gameplay::Ray::INTERSECTS_NONE) {
			return true;
		}
	} 

	return false;
}

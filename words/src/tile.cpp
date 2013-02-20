#include "tile.hpp"

using namespace gameplay;

///-----------------------------------------------------------------------------------------------

TileLayer::TileLayer() {
}

void TileLayer::SetRenderableNode(gameplay::Node* renderable_node) {
	this->renderable_node = renderable_node;
}

///-----------------------------------------------------------------------------------------------

Tile::Tile(gameplay::Node* physics_node) {
	layers.reserve(8);
	this->physics_node = physics_node;
}

void createBillboardHelper(const Vector3& objectPosition, const Vector3& cameraPosition,
								   const Vector3& cameraUpVector, const Vector3* cameraForwardVector,
								   Matrix* dst)
{
	Vector3 delta(objectPosition, cameraPosition);
	bool isSufficientDelta = false;//delta.lengthSquared() > MATH_EPSILON;

	dst->setIdentity();
	dst->m[3] = objectPosition.x;
	dst->m[7] = objectPosition.y;
	dst->m[11] = objectPosition.z;

	// As per the contracts for the 2 variants of createBillboard, we need
	// either a safe default or a sufficient distance between object and camera.
	if (cameraForwardVector || isSufficientDelta)
	{
		Vector3 target = isSufficientDelta ? cameraPosition : (objectPosition - *cameraForwardVector);

		// A billboard is the inverse of a lookAt rotation
		Matrix lookAt;
		Matrix::createLookAt(objectPosition, target, cameraUpVector, &lookAt);
		dst->m[0] = lookAt.m[0];
		dst->m[1] = lookAt.m[4];
		dst->m[2] = lookAt.m[8];
		dst->m[4] = lookAt.m[1];
		dst->m[5] = lookAt.m[5];
		dst->m[6] = lookAt.m[9];
		dst->m[8] = lookAt.m[2];
		dst->m[9] = lookAt.m[6];
		dst->m[10] = lookAt.m[10];
	}
}

gameplay::Quaternion Tile::getBillboardTransformation(gameplay::Camera* camera) {
	//update the first nodes position so we can use it to figure out the billboard transformation
	physics_node->setTranslation(position.x, position.y, position.z);

	gameplay::Quaternion q, p;
	gameplay::Matrix m, m2;

	createBillboardHelper(physics_node->getTranslationWorld(), camera->getNode()->getTranslationWorld(), camera->getNode()->getUpVectorWorld(), &camera->getNode()->getForwardVector(), &m);

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
}

void Tile::SetPosition(int x, int y, int z) {
	position.x = x;
	position.y = y;
	position.z = z;
}

void Tile::Render(gameplay::Camera* camera) {
	gameplay::Quaternion p;
	gameplay::Matrix m;

	m.rotateX(90 * (MATH_PI / 180));
	m.getRotation(&p);

	p = getBillboardTransformation(camera);

	//make sure the physics node is also where it needs to be
	physics_node->setTranslation(position.x, position.y, position.z);
	physics_node->setRotation(p);

	for(unsigned int i = 0; i < layers.size(); i++) {
		TileLayer* tileLayer = layers[i];
		if (tileLayer && tileLayer->renderable_node) {
			//update the renderable node and draw it where we need to
			tileLayer->renderable_node->setTranslation(position.x, position.y, position.z);
			tileLayer->renderable_node->setRotation(p);


		
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

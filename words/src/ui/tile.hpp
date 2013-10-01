#ifndef __TILE__hpp
#define __TILE__hpp

#include <vector>
#include <math.h>

#include "gameplay.h"
#include "letter_controller.hpp"
#include "../board/dice_manager.hpp"

class Tile;
class LetterController;

class TileLayer {
friend class Tile;
private:
	/// @summary	The node for this tile.
	gameplay::Node* renderable_node;
protected:
	/// Default constructor.
	TileLayer();
public:
	/// Sets a renderable node.
	/// @param [in,out]	renderable_node	If non-null, the renderable node.
	void SetRenderableNode(gameplay::Node* renderable_node);
};

///-----------------------------------------------------------------------------------------------

class Tile {
private:
	enum Animation { NONE, DELAYING_TO_MOVE, MOVING, SHRINKING, POPPING, POPPING_SNAP_BACK};

	/// @summary	The layers.
	std::vector<TileLayer*> layers;

	/// @summary	Target position.
	gameplay::Vector3 target_position;

	/// @summary	The animation.
	Animation animation;

	/// @summary	The move delay.
	float move_delay;

	/// Gets a billboard transformation.
	/// @param [in,out]	camera	If non-null, the camera.
	/// @return	The billboard transformation.
	gameplay::Quaternion getBillboardTransformation(gameplay::Camera* camera);

	/// @summary	The physics node.
	gameplay::Node* physics_node;

	//the scale factor of the physics node
	float physics_node_scale;

	/// @summary	The letter controller.
	LetterController* letterController;

	/// @summary	true if translation is dirty.
	bool translation_is_dirty;
public:
	/// Values for the layer types and their order.
	enum LayerLevel {BASE, ICON, SCORE};
	
	/// Constructor.
	/// @param [in,out]	physics_node	If non-null, the physics node.
	Tile(gameplay::Node* physics_node, LetterController* letterController);

	/// @summary	true if this object is visible.
	bool is_visible;

	/// @summary	true if this object is selected.
	bool is_selected;

	/// @summary	The scale.
	float scale;

	/// @summary	The cell thats attached to this tile
	BoardCell* cell;

	/// @summary	The value of this tile (as text)
	std::string value;

	/// @summary	The position.
	gameplay::Vector3 position;

	/// @summary	Zero-based index of the row.
	int row_index;

	/// @summary	Zero-based index of the col.
	int col_index;

	/// Creates a layer of the specified type
	///
	/// @param	layer		 	The layer.
	/// @param [in,out]	scene	If non-null, the scene.
	/// @param [in,out]	renderable_node 	If non-null, the node.
	void CreateLayer(LayerLevel layer, gameplay::Scene* scene, gameplay::Node* renderable_node = NULL);

	/// Gets a layer.
	/// @param	layer	The layer.
	/// @return	The layer.
	TileLayer* GetLayer(LayerLevel layer);

	/// Sets a position of this tile
	/// @param	x	The x coordinate.
	/// @param	y	The y coordinate.
	/// @param	z	The z coordinate.
	void SetPosition(int x, int y, int z);

	/// Sets a target position to translate to
	/// @param	x	The x coordinate.
	/// @param	y	The y coordinate.
	/// @param	z	The z coordinate.
	/// @param	delay	the delay
	void TranslateTo(int x, int y, int z, float delay);

	/// Applies the translation animation
	void ApplyTranslation();

	/// Play pop animation.
	void PlayPopAnimation();

	/// Play shrinking animation.
	void PlayShrinkingAnimation();

	/// Updates this object.
	/// @param	dt			  	The dt.
	void Update(float dt);

	/// Renders the given camera.
	/// @param [in,out]	camera	If non-null, the camera.
	void Render(gameplay::Camera* camera);

	/// Query if this object intersects the given ray.
	/// @param [in,out]	ray	The ray.
	/// @return	true if it succeeds, false if it fails.
	bool Intersects(gameplay::Ray& ray);

	static void createBillboardHelper(const gameplay::Vector3& objectPosition, const gameplay::Vector3& cameraPosition,
		const gameplay::Vector3& cameraUpVector, const gameplay::Vector3& cameraForwardVector,
		gameplay::Matrix* dst);
};


#endif  // __TILE__hpp
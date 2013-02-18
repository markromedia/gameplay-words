#ifndef __TILE__hpp
#define __TILE__hpp

#include <vector>
#include <math.h>

#include "gameplay.h"

class Tile;

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
	/// @summary	The layers.
	std::vector<TileLayer*> layers;

	/// @summary	The position.
 	gameplay::Vector3 position;
public:
	/// Default constructor.
	Tile();

	/// Values for the layer types and their order.
	enum LayerLevel {BASE, ICON};

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

	/// Updates this object.
	/// @param	dt			  	The dt.
	void Update(float dt);

	/// Renders the given camera.
	/// @param [in,out]	camera	If non-null, the camera.
	void Render(gameplay::Camera* camera);
};


#endif  // __TILE__hpp
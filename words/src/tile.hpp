#ifndef __TILE__hpp
#define __TILE__hpp

#include <vector>

#include "gameplay.h"

class Tile;

class TileLayer {
friend class Tile;
private:
	/// @summary	The node for this tile.
	gameplay::Node* node;
protected:

	/// Default constructor.
	TileLayer();

public:
	/// Sets a material.
	/// @param [in,out]	material	If non-null, the material.
	void SetMaterial(gameplay::Material* material);
};

///-----------------------------------------------------------------------------------------------

class Tile {
private:
	/// @summary	The layers.
	std::vector<TileLayer*> layers;

	/// @summary	The base layer.
	TileLayer* base_layer;

	/// @summary	The letter layer.
	TileLayer* icon_layer;

	/// @summary	The position.
 	gameplay::Vector3 position;

public:
	/// Default constructor.
	Tile();

	/// @summary	The transform.
	gameplay::Matrix transform;

	/// Creates a base layer.
	///
	/// @param [in,out]	scene	If non-null, the scene.
	/// @param [in,out]	model	If non-null, the model.
	void CreateBaseLayer(gameplay::Scene* scene, gameplay::Model* model);

	/// Creates an icon layer.
	///
	/// @param [in,out]	scene			If non-null, the scene.
	/// @param [in,out]	letter_model	If non-null, the letter model.
	void CreateIconLayer(gameplay::Scene* scene, gameplay::Model* letter_model);

	/// Sets a position of this tile
	/// @param	x	The x coordinate.
	/// @param	y	The y coordinate.
	/// @param	z	The z coordinate.
	void SetPosition(int x, int y, int z);

	/// Updates this object.
	/// @param [in,out]	scene	If non-null, the scene.
	/// @param	dt			 	The dt.
	void Update(gameplay::Scene* scene, float dt);

	/// Renders this object.
	void Render();
};


#endif  // __TILE__hpp
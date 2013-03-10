#ifndef __SELECTED_TEXT_CONNECTOR__hpp
#define __SELECTED_TEXT_CONNECTOR__hpp

#include <vector>

#include "gameplay.h"
#include "tile.hpp"
#include "renderable_node_repository.hpp"

class SelectedTextConnector {
private:
	/// @summary	The connector node.
	gameplay::Node* connector_node;

	/// @summary	The connector batch.
	gameplay::SpriteBatch* connector_batch;

	/// @summary	Width/Height of the model.
	int model_width, model_height;
	
	/// @summary	The instance.
	static SelectedTextConnector* instance;

	/// Gets a billboard transformation.
	/// @param [in,out]	camera	If non-null, the camera.
	/// @return	The billboard transformation.
	static gameplay::Quaternion getBillboardTransformation(gameplay::Camera* camera);
public:
	/// Initialises this object.
	static void Init();

	/// Draws the connectors for the provided 
	///
	/// @param [in,out]	tiles_to_draw	If non-null, the tiles to draw.
	static void Draw(gameplay::Camera* camera, std::vector<Tile*> tiles_to_draw);

};

#endif  // __SELECTED_TEXT_CONNECTOR__hpp
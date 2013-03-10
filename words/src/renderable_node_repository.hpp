#ifndef __RENDERABLE_NODE_REPOSITORY__hpp
#define __RENDERABLE_NODE_REPOSITORY__hpp

/// utility macro for access materials
/// @param	id	The identifier.
#define RENDERABLE(id) RenderableNodeRepository::_()[id]

#include <map>

#include "gameplay.h"

class RenderableNodeRepository {
private:
	std::map<std::string, gameplay::Node*> renderable_node_map;

	/// @summary	The singlton instance.
	static RenderableNodeRepository* instance;

	/// Initializes a renderable node
	/// @param	id				  	The identifier.
	/// @param	material		  	The material.
	/// @param [in,out]	model_node	If non-null, the model node.
	/// @param [in,out]	scene	  	If non-null, the scene.
	void initializeNode(std::string id, const char* material, gameplay::Node* model_node, gameplay::Scene* scene);

	/// Creates the connector node.
	void initConnectorNode(gameplay::Node* model_node, gameplay::Scene* scene);
public:
	static void Init(gameplay::Scene* scene);

	/// Retrives singleton
	/// @return	null if it fails, else.
	static RenderableNodeRepository* get();

	/// convience method for retrieving node using subscript. e.g.
	/// <code>RenderableNodeRepository::_["renderable_node_id"]</code>
	/// @return	singleton renderable node repo
	static RenderableNodeRepository &_();

	/// Gets a renderable node.
	/// @param	id	The identifier.
	/// @return	null if it fails, else the renderable node.
	gameplay::Node* getRenderableNode(std::string id);

	/// Array indexer operator.
	/// @param	parameter1	The first parameter.
	/// @return	The indexed value.
	gameplay::Node* &operator[] (std::string id);
};


#endif  // __RENDERABLE_NODE_REPOSITORY__hpp
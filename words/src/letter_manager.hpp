#ifndef __LETTER_MANAGER__hpp
#define __LETTER_MANAGER__hpp

#include <vector>

#include "gameplay.h"
#include "tile.hpp"
#include "renderable_node_repository.hpp"


class LetterManager {
private:
	/// Default constructor.
	LetterManager();

	/// @summary	The instance.
	static LetterManager* instance;

	std::vector<Tile*> tiles;
	std::vector<Tile*> renderables;
public:
	/// Initialises this object.
	/// @param [in,out]	scene	If non-null, the scene.
	static void Init(gameplay::Scene* scene);

	/// Gets the singleton instance.
	/// @return	null if it fails, else.
	static LetterManager* get();

	static void Render(gameplay::Camera* camera);

	void Update(float dt);
};


#endif  // __LETTER_MANAGER__hpp
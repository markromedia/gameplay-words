#ifndef __LETTER_MANAGER__hpp
#define __LETTER_MANAGER__hpp

#include <vector>

#include "gameplay.h"
#include "tile.hpp"
#include "renderable_node_repository.hpp"


class LetterController {
private:
	/// Default constructor.
	LetterController();

	/// @summary	The instance.
	static LetterController* instance;

	std::vector<Tile*> tiles;
	std::vector<Tile*> renderables;
public:
	/// Initialises this object.
	/// @param [in,out]	scene	If non-null, the scene.
	static void Init(gameplay::Scene* scene);

	/// Gets the singleton instance.
	/// @return	null if it fails, else.
	static LetterController* get();

	/// Handles the touch down event.
	/// @param	ray the calculated ray
	/// @param	x	The x coordinate.
	/// @param	y	The y coordinate.
	/// @return	true if it succeeds, false if it fails.
	static bool HandleTouchDownEvent(gameplay::Ray& ray, int x, int y);

	/// Handles the touch up event.
	static void HandleTouchUpEvent();

	static void Render(gameplay::Camera* camera);

	void Update(float dt);
};


#endif  // __LETTER_MANAGER__hpp
#ifndef __SCENE_MANAGER__hpp
#define __SCENE_MANAGER__hpp

#include <string>
#include <sstream>
#include <vector>

#include "../scene.hpp"
#include "../game/game_scene.hpp"
#include "../words.h"
#include "../input_event_handler.hpp"
#include "gameplay.h"

class SceneManager {
private:
	/// @summary	The current scene.
	Words::Scene* current_scene;

	/// Default constructor.
	SceneManager();

	/// @summary	The scenes.
	std::vector<Words::Scene*> scenes;

	/// @summary	The instance.
	static SceneManager* instance;
public:

	/// Delegate touch event.
	/// @param [in,out]	app	If non-null, the application.
	/// @param	type	   	The type.
	/// @param [in,out]	ray	The ray.
	/// @param	x		   	The x coordinate.
	/// @param	y		   	The y coordinate.
	///
	/// @return	true if it succeeds, false if it fails.
	bool DelegateTouchEvent(words* app, TouchState type, gameplay::Ray& ray, int x, int y );

	/// Goto menu scene.
	/// @param	is_game_over	true if this object is game over.
	void GotoMenuScene(bool is_game_over);

	/// Goes to the game scene
	void GotoGameScene();

	/// Starts a new game.
	void StartNewGame();

	/// Initialises this object.
	static void Init();

	/// Returns singleton
	/// @return	null if it fails, else.
	static SceneManager* get();

	/// Basic update function
	/// @param	elapsedTime	Time of the elapsed.
	void Update(float elapsedTime);

	/// Render this scene
	void Render();
};

#endif  // __SCENE_MANAGER__hpp
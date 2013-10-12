#ifndef __GAME__hpp
#define __GAME__hpp

#include "../scene.hpp"

class GameScene : public Words::Scene {
private:

	/// @summary	The instance.
	static GameScene* instance;

	/// @summary	The scene.
	gameplay::Scene* scene;
public:
	/// Initialises this object.
	/// @param [in,out]	scene	If non-null, the scene.
	static void Init(gameplay::Scene* scene);

	/// Returns static instance
	/// @return	null if it fails, else.
	static GameScene* Get();

	/// <inheritdoc />
	virtual bool HandleTouchDownEvent(gameplay::Ray& ray, int x, int y);

	/// <inheritdoc />
	virtual bool HandleTouchUpEvent(gameplay::Ray& ray, int x, int y) ;

	/// <inheritdoc />
	virtual void Update(float elapsedTime);

	/// <inheritdoc />
	virtual void Render();

	/// Sets up the game for a new game
	void NewGame();

	/// Called when a game is over
	void GameOver();
};

#endif  // __GAME__hpp
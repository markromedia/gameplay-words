#include "../src/ext/scene_manager.hpp"

#include "../src/game/game_scene.hpp"
#include "../src/scene.hpp"
#include "../src/menu/menu.hpp"

SceneManager* SceneManager::instance = NULL;

SceneManager::SceneManager()
{
	this->scenes.push_back(GameScene::Get());
	this->scenes.push_back(new Menu());
}

void SceneManager::Init()
{
	SceneManager::instance = new SceneManager();
}


SceneManager* SceneManager::get()
{
	return SceneManager::instance;
}

bool SceneManager::DelegateTouchEvent(words* app, TouchState type, gameplay::Ray& ray, int x, int y )
{
	if (current_scene) {
		if (type == TOUCH_DOWN) {
			return current_scene->HandleTouchDownEvent(ray, x, y);	
		} else if (type == TOUCH_UP) {
			return current_scene->HandleTouchUpEvent(ray, x, y);	
		}  
	} 
	return false;
}

void SceneManager::GotoMenuScene(bool is_game_over)
{
	this->current_scene = scenes[1];
	((Menu*) this->current_scene)->SetIsGameOver(is_game_over);
}

void SceneManager::GotoGameScene()
{
	this->current_scene = scenes[0];
}

void SceneManager::Update( float elapsedTime )
{
	if (this->current_scene) {
		this->current_scene->Update(elapsedTime);
	}
}

void SceneManager::Render()
{
	if (this->current_scene) {
		this->current_scene->Render();
	}
}

void SceneManager::StartNewGame()
{
	GameScene::Get()->NewGame();
	this->GotoGameScene();
}


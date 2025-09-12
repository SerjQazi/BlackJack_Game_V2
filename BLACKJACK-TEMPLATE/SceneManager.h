#pragma once

#include "Scene.h"
#include "Camera.h"
#include "World.h"
#include "GameConfiguration.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	template <typename T>
	T* createScene(std::string goID, Camera* c, World* w)
	{
		static_assert(std::is_base_of<Scene, T>::value, "Error: T must be derived from Scene");

		currentCamera = c;
		currentWorld = w;
		T* scene = new T(goID, currentCamera, currentWorld);

		if(currentWorld)
			currentWorld->addBody(scene);

		gameScenes.push_back(scene);
		return scene;
	}
	void addScene(Scene*, Camera* c, World* w);
	void removeScene();

	void update(float delta);
	void render();

	static SceneManager* getInstance();
	static void removeInstance();

	std::vector<Scene*> gameScenes;

	static Camera* currentCamera;
	static World* currentWorld;

private:
	static SceneManager* instance;
};
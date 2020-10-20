#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Shader.h"

#include "list"


class Event;
class GameObject;

enum GOType;

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void addGameObject(GameObject* _go);
	void Draw(Shader _shader);
	void DebugDraw(Shader _shader);
	void BackgroundgDraw(Shader _shader, unsigned int texture, bool front);
	void RopeDraw(Shader _shader);
	void FinishDraw(Shader _shader);
	void FSDraw(Shader _shader, float color);
	void Update();
	void HandleEvent(Event* ev);
	void DeleteObjects();
	
	GameObject* getGO(GOType _t);
public:
	std::list<GameObject*> mpGameObjects;
private:
private:
};
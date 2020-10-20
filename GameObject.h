#pragma once
#ifndef _GO_H_
#define _GO_H_

#include "list"

enum ComponentType;

class Component;
class Shader;
class Event;

enum GOType
{
	TYPE_PLAYER = 0,
	TYPE_BLADE,
	TYPE_SHOOTER,
	TYPE_BULLET,
	TYPE_BOOSTER
};

class GameObject
{
public:
	GameObject();
	~GameObject();

	Component* getComponent(ComponentType _type);
	void addComponent(Component* newComp);

	GameObject const& operator=(GameObject const& _copy);

	void HandleEvent(Event* ev);

	void Update();
	void Draw(Shader _shader);
public:
	GOType type;
	bool del;
	int bulletHits;
	std::list<Component*> mpComponents;
private:
private:
};


#endif

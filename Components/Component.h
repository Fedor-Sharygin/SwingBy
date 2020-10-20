#pragma once
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class GameObject;

enum ComponentType
{
	TYPE_TRANSFORM = 0,
	TYPE_SHAPE,
	TYPE_CIRCLE_MOVE,
	TYPE_UP_DOWN,
	TYPE_SHOOT,
	TYPE_BOOST,
	TYPE_PHYSICS,
	TYPE_BOUND_SHAPE,
	TYPE_CONTROL
};

class Component
{
public:
	Component(ComponentType _type);
	~Component();

	virtual void Update() {};

	virtual void Serialize(json& j) {};
public:
	ComponentType type;
	GameObject* mpOwner;
private:
private:
};


#endif

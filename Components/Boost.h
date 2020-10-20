#pragma once

#ifndef BOOST_H
#define BOOST_H

#include "glm/glm.hpp"

#include "Component.h"


class Boost : public Component
{
public:
	Boost() : Component(TYPE_BOOST), triggered(false) {};
	~Boost() {};

	void Update() {};
	void Serialize(json& j);
public:
	glm::vec3 speedBoost;

	bool triggered;
private:
private:
};



#endif

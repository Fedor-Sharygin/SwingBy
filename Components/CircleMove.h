#pragma once

#ifndef _CIRCLE_MOVE_H_
#define _CIRCLE_MOVE_H_

#include <glm/glm.hpp>

#include "Component.h"


using namespace glm;

class CircleMove : public Component
{
public:
	CircleMove();
	~CircleMove();

	void Update();
	
	void Serialize(json& j);
public:
private:
private:
	float rotationSpeed;	// in degrees
};


#endif


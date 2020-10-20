#pragma once

#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "Component.h"

#include "glm/glm.hpp"


class Control : public Component
{
public:
	Control() : Component(TYPE_CONTROL) {};
	~Control() {};

	void Update();
public:
private:
private:
};


#endif


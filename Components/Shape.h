#pragma once

#ifndef SHAPE_H
#define SHAPE_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "list"
#include <string>
#include <utility>

#include "Component.h"
#include "Model.h"


class Shader;

class Shape : public Component
{
public:
	Shape();
	~Shape();

	void Update();
	void Draw(Shader _shader);

	void Serialize(json &j);
public:
	// contains all the information about the model
	Model* shape;
private:
private:
};


#endif


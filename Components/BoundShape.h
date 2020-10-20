#pragma once

#ifndef BS_H
#define BS_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Component.h"


enum BoundType
{
	TYPE_AABB,
	TYPE_LINE,
	NUM_OF_TYPES
};

class Shader;

class BoundShape : public Component
{
public:
	BoundShape(BoundType _t) : Component(TYPE_BOUND_SHAPE), bsType(_t) {};
	~BoundShape() {};

	virtual void Update() {};
	virtual void Serialize(json& j) {};
	virtual void Draw(Shader _s) = 0;
public:
	BoundType bsType;
private:
private:
};


class AABB : public BoundShape
{
public:
	AABB() : BoundShape(TYPE_AABB) {};
	~AABB() {};

	void Update();
	void Serialize(json& j);
	void Draw(Shader _s);
public:
	glm::vec2 mCenter;
	float width, height;
private:
private:
};


class Line : public BoundShape
{
public:
	Line() : BoundShape(TYPE_LINE) {};
	~Line() {};

	void Update();
	void Serialize(json& j);
	void Draw(Shader _s);
public:
	glm::vec2 start;
	
	float length;
	float tilt, origTilt;
private:
private:
};


#endif

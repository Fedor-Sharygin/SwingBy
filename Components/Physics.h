#pragma once

#ifndef PHYSIC_H
#define PHYSIC_H

#include <glm/glm.hpp>

#include "Component.h"


class Shader;

class Physics : public Component
{
public:
	Physics() : Component(TYPE_PHYSICS),
		pullForce(glm::vec3(0.0f)), gravity(glm::vec3(0.0f, -100.0f, 0.0f)),
		mass(1.0f), speed(glm::vec3(0.0f)), grappled(false)
	{};
	~Physics() {};

	void setGrapplePoint();
	void Update();
	void Serialize(json& j) {};
	void Draw(Shader _s);
public:
//	BoundShape* boundary;
	float mass;
	glm::vec3 pullForce;
	glm::vec3 gravity;
	glm::vec3 allForces;

	bool grappled;
	glm::vec3 grapplePoint;
	float sqDistance;

	glm::vec3 speed;
private:
private:
};




#endif


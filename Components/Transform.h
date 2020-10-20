#pragma once
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Component.h"
#include "glm/glm.hpp"

class Transform : public Component
{
public:
	Transform();
	~Transform();

	void setPosition(glm::vec3 newPos) { position = newPos; };
	glm::vec3 getPosition() { return position; };

	void setSize(glm::vec3 newScale) { scaleSize = newScale; };
	glm::vec3 getSize() { return scaleSize; };

	void setSpin(float newSpin) { spin = newSpin; };
	void setTilt(float newTilt) { tilt = newTilt; };
	void setYaw(float newYaw) { yaw = newYaw; };
	float getSpin() { return spin; };
	float getTilt() { return tilt; };
	float getYaw() { return yaw; };

	void Update();

	void Serialize(json& j);
public:
	glm::vec3 lastPos;
private:
private:
	// the position of the object
	glm::vec3 position;

	// in degrees
	float spin, tilt, yaw;

	// size of the object
	glm::vec3 scaleSize;
};


#endif

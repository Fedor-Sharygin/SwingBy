#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace glm;


class Camera
{
public:
	Camera(vec3 stPos = vec3(-450.0f, 0.0f, 0.0f), vec3 stFr = vec3(1.0f, 0.0f, 0.0f),
		vec3 stUp = vec3(0.0f, 1.0f, 0.0f),
		float _spin = -90.0f, float _tilt = 0.0f, double _zoom = 45.0f)
		:
		camPos(stPos), camFront(stFr), camUp(stUp), spin(_spin), tilt(_tilt), zoom(_zoom)
	{};
	~Camera() {};
public:
	vec3 camPos;
	vec3 camFront;
	vec3 camUp;
	float spin, tilt;
	double zoom;
private:
private:
};
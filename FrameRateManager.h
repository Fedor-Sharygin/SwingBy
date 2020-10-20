#pragma once


#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "limits.h"

class FrameRateManager
{
public:
	FrameRateManager(unsigned int MaxFrameRate);
	~FrameRateManager() {};

	float FrameTime() { return mFrameTime; };

	void FrameStart();
	void FrameEnd();
public:
private:
private:
	float mFrameStart;
	float mFrameEnd;
	float mFrameTime;
	unsigned int FrameRate;
	unsigned int TicksPerFrame;
};

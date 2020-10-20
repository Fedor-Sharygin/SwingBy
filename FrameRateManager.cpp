#include "FrameRateManager.h"
#include <cstdio>

FrameRateManager::FrameRateManager(unsigned int MaxFrameRate)
{
	if (MaxFrameRate == 0)
		MaxFrameRate = UINT_MAX;

	FrameRate = MaxFrameRate;
	TicksPerFrame = 1000 / FrameRate;

	mFrameStart = 0.0f;
	mFrameEnd = 0.0f;
	mFrameTime = 0.0f;
}

void FrameRateManager::FrameStart()
{
	mFrameStart = glfwGetTime();
//	printf("%f\n", mFrameStart);
}

void FrameRateManager::FrameEnd()
{
	mFrameEnd = glfwGetTime();
//	printf("%f\n", mFrameEnd);

	while ((mFrameEnd - mFrameStart) < (float(TicksPerFrame) / 1000.0f))
		mFrameEnd = glfwGetTime();

	mFrameTime = mFrameEnd - mFrameStart;
//	printf("%f\n", mFrameTime);
}


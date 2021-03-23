#pragma warning (disable: 4244)
// loss data from converting uint64 to float warning
#include "TimeUtils.h"
#include <iostream>
#include <cassert>


//static const float DESIRED_FPS = 60.0f;
//static const float DESIRED_FRAMETIME_MS = 1000.0f / DESIRED_FPS;
//static const float MAX_FRAMETIME_MS = 2 * DESIRED_FRAMETIME_MS;

//static LARGE_INTEGER PerformanceFrequency = { 0 };
//static long lastFrameStartTick_ = 0;
//static float lastFrameTime_ms_ = 0;

float GetLastFrameTime_ms()
{
	return lastFrameTime_ms_;
}

float CalculateLastFrameTime_ms()
{
	// grab the CPU tick counter
	tick_t currentTick = tick_t(GetCurrentTickCounter());

	if (lastFrameStartTick_)
	{
		//tick_t elapsedTicks = currentTick - lastFrameStartTick_;
		assert(PerformanceFrequency.QuadPart != 0);
		lastFrameTime_ms_ =(1000.0* (currentTick - lastFrameStartTick_)) / static_cast<float>(PerformanceFrequency.QuadPart);
	}
	else
	{
		lastFrameTime_ms_ = 16.6f;
	}
	// save current frame tick
	lastFrameStartTick_ = currentTick;

	return lastFrameTime_ms_;
}

tick_t GetCurrentTickCounter()
{
	LARGE_INTEGER CurrentFrameCounter;
	QueryPerformanceCounter(&CurrentFrameCounter);
	return CurrentFrameCounter.QuadPart;
}

void GetPerformanceFrequency()
{
	QueryPerformanceFrequency(&PerformanceFrequency);
}

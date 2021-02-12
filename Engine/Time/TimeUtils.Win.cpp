#include "TimeUtils.h"
#include <iostream>


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
	tick_t currentTick = GetCurrentTickCounter();

	if (lastFrameStartTick_)
	{
		tick_t elapsedTicks = currentTick - lastFrameStartTick_;
		lastFrameTime_ms_ = 1000.0f*float(elapsedTicks / (float)PerformanceFrequency.QuadPart);
	}
	else
	{
		lastFrameTime_ms_ = DESIRED_FRAMETIME_MS;
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

//int main() {
//	GetPerformanceFrequency();
//	while (1) {
//		std::cout << CalculateLastFrameTime_ms() << std::endl;
//		//std::cout << PerformanceFrequency.QuadPart << std::endl;
//	}
//}
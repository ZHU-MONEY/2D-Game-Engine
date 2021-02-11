#pragma once
#ifndef TIME_UTILS_
#define TIME_UTILS_
#include <Windows.h>

	//typedef uint64_t	tick_t;
	static float GetLastFrameTime_ms();
	static float CalculateLastFrameTime_ms();

	static const float DESIRED_FPS=60.0f;;
	static const float DESIRED_FRAMETIME_MS = 1000.0f / DESIRED_FPS;
	static const float MAX_FRAMETIME_MS = 2 * DESIRED_FRAMETIME_MS;
	
	static LARGE_INTEGER PerformanceFrequency;
	static double lastFrameStartTick_;
	static float lastFrameTime_ms_;

	static double GetCurrentTickCounter();
	static void GetPerformanceFrequency();


#endif // !TIME_UTILS_

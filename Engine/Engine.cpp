#include "Engine.h"
#include "Engine/Time/TimeUtils.Win.cpp"
#include "Engine/Time/TimeUtils.h"
#include "Glib/GLib.h"

namespace Engine {
	static bool requestQuit = false;
	bool StartUp()
	{
		PhysicsSystem::Create();
		Renderer::Create();

		GetPerformanceFrequency();

		requestQuit = false;

		return true;
	}

	void Run()
	{
		GLib::Service(requestQuit);
		CalculateLastFrameTime_ms();
		float dt = GetLastFrameTime_ms();

		PhysicsSystem* physicsSystemInstance = PhysicsSystem::GetInstance();
		Renderer* rendererInstance = Renderer::GetInstance();

		physicsSystemInstance->Run(dt);
		rendererInstance->Run();
	}

	void Shutdown()
	{
	}
}

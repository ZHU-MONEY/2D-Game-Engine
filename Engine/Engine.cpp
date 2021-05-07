#include "Engine.h"
#include "Engine/Time/TimeUtils.Win.cpp"
#include "Engine/Time/TimeUtils.h"
#include "Glib/GLib.h"
#include "Engine/Input/InputReader.h"

namespace Engine {
	bool StartUp()
	{
		PhysicsSystem::Create();
		ColliderSystem::Create();
		Renderer::Create();
		InputReader::Create();

		GetPerformanceFrequency();

		char			Buffer[65];
		sprintf_s(Buffer, 65, "Engine Starting \n");
		OutputDebugStringA(Buffer);
		return true;
	}

	void Run()
	{
		CalculateLastFrameTime_ms();
		float dt = GetLastFrameTime_ms();

		PhysicsSystem* physicsSystemInstance = PhysicsSystem::GetInstance();
		ColliderSystem* colliderSystemInstance = ColliderSystem::GetInstance();
		Renderer* rendererInstance = Renderer::GetInstance();
		InputReader* inputReaderInstance = InputReader::GetInstance();

		physicsSystemInstance->Run(dt);
		colliderSystemInstance->Run(dt);
		rendererInstance->Run();
	}

	void Shutdown()
	{
		PhysicsSystem* physicsSystemInstance = PhysicsSystem::GetInstance();
		ColliderSystem* colliderSystemInstance = ColliderSystem::GetInstance();
		Renderer* rendererInstance = Renderer::GetInstance();
		InputReader* inputReaderInstance = InputReader::GetInstance();

		physicsSystemInstance->Destroy();
		colliderSystemInstance->Destroy();
		rendererInstance->Destroy();
		inputReaderInstance->Destroy();
		char			Buffer[65];
		sprintf_s(Buffer, 65, "Engine Shutdown \n");
		OutputDebugStringA(Buffer);
	}
}

#include "Engine.h"
#include "Engine/Time/TimeUtils.Win.cpp"
#include "Engine/Time/TimeUtils.h"
#include "Glib/GLib.h"
#include "Engine/Input/InputReader.h"

namespace Engine {
	static bool requestQuit = false;
	bool StartUp()
	{
		PhysicsSystem::Create();
		ColliderSystem::Create();
		Renderer::Create();
		InputReader::Create();

		GetPerformanceFrequency();

		requestQuit = false;

		return true;
	}

	void Run()
	{
		//GLib::Service(requestQuit);
		CalculateLastFrameTime_ms();
		float dt = GetLastFrameTime_ms();

		PhysicsSystem* physicsSystemInstance = PhysicsSystem::GetInstance();
		ColliderSystem* colliderSystemInstance = ColliderSystem::GetInstance();
		Renderer* rendererInstance = Renderer::GetInstance();
		InputReader* inputReaderInstance = InputReader::GetInstance();

		//const size_t	lenBuffer = 65;
		//char			Buffer[lenBuffer];
		//sprintf_s(Buffer, lenBuffer, "AAA  %s\n", InputReader::isKey_A_Down ? "A is DOWN" : "A is UP");
		//OutputDebugStringA(Buffer);

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
	}
}

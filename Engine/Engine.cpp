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
		Renderer* rendererInstance = Renderer::GetInstance();
		InputReader* inputReaderInstance = InputReader::GetInstance();

		const size_t	lenBuffer = 65;
		char			Buffer[lenBuffer];

		//sprintf_s(Buffer, lenBuffer, "VKey %04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
		sprintf_s(Buffer, lenBuffer, "AAA  %s\n", InputReader::isKey_A_Down ? "A is DOWN" : "A is UP");
		OutputDebugStringA(Buffer);

		physicsSystemInstance->Run(dt);
		rendererInstance->Run();
	}

	void Shutdown()
	{
	}
}

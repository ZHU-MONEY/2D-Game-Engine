#include "Engine.h"
#include "Engine/Time/TimeUtils.Win.cpp"
#include "Engine/Time/TimeUtils.h"
namespace Engine {
    bool StartUp()
    {
        PhysicsSystem::Create();
        GetPerformanceFrequency();

        return true;
    }

    void Run()
    {
        PhysicsSystem* physicsSystemInstance = PhysicsSystem::GetInstance();

        CalculateLastFrameTime_ms();
        float dt = GetLastFrameTime_ms();
        physicsSystemInstance->Run(dt);
    }

    void Shutdown()
    {
    }
}

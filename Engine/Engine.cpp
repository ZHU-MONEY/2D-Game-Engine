#include "Engine.h"
#include "Engine/Time/TimeUtils.Win.cpp"
#include "Engine/Time/TimeUtils.h"

namespace Engine {
    bool StartUp()
    {
        PhysicsSystem::Create();
        Renderer::Create();
        
        GetPerformanceFrequency();

        return true;
    }

    void Run()
    {
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

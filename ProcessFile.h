#pragma once
#include <functional>
#include "Engine/HashedString/HashedString.h"
#include "Engine/JobSystem/JobStatus.h"
#include <Engine\JobSystem\JobSystem.h>
#include "Engine/GameObject/JsonGameObjectUtils.h"
#include <string>
class ProcessFile
{
private:
	const char* m_pFilename;
	std::function<StrongPtr<GameObject>(const char*)>  m_Processor;
	Engine::HashedString m_QueueName;
	Engine::JobSystem::JobStatus* m_pJobStatus;

public:
	ProcessFile(const char* i_pFilename,std::function<StrongPtr<GameObject>(const char*)> i_Processor, const Engine::HashedString i_QueueName = Engine::JobSystem::GetDefaultQueue(), Engine::JobSystem::JobStatus* i_pJobStatus = nullptr);

	void operator() ();



};


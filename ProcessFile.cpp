#include "ProcessFile.h"

ProcessFile::ProcessFile(const char* i_pFilename, std::function<StrongPtr<GameObject>(const char*)> i_Processor, const Engine::HashedString i_QueueName, Engine::JobSystem::JobStatus* i_pJobStatus) :
	m_pFilename(i_pFilename),
	m_Processor(i_Processor),
	m_QueueName(i_QueueName),
	m_pJobStatus(i_pJobStatus)
{
}

void ProcessFile::operator()()
{
	if (m_pFilename)
	{
		std::string filePath = m_pFilename;

		std::function<StrongPtr<GameObject>(const char*)> func = m_Processor;
		Engine::JobSystem::RunJob(
			m_QueueName,
			[filePath]() {
				JsonGameObjectUtils::CreateGameObjectFromJson(filePath.c_str());
			},
			m_pJobStatus, "ProcessFileContents"
				);
	}
}



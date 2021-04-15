#include "MonsterChaseGame.h"
#include "Engine/Time/TimeUtils.Win.cpp"
#include "Engine/Time/TimeUtils.h"
#include <Engine\Input\InputReader.h>
#include "Engine/Physics/PhysicsObject.h"
#include "Engine/Render/Renderer.h"
#include "Engine/GameObject/JsonGameObjectUtils.h"
#include <Engine\HashedString\HashedString.h>
#include <Engine\JobSystem\JobSystem.h>
#include "ProcessFile.h"

namespace Game {
	bool StartUp()
	{
		// create an instance of the game
		MonsterChaseGame* mc_instance = MonsterChaseGame::Create();

		if (mc_instance == nullptr)
		{
			return false;
		}

		// initialize the game
		mc_instance->Initialize();
		return true;
	}

	void Shutdown()
	{
		MonsterChaseGame::Destroy();
	}

	// static member initialization
	MonsterChaseGame* MonsterChaseGame::instance_ = nullptr;
	bool MonsterChaseGame::quitMonsterChaseGame = false;
	MonsterChaseGame::MonsterChaseGame()
	{
		player_ = nullptr;
	}

	MonsterChaseGame::~MonsterChaseGame()
	{
		/*delete player_;
		player_ = nullptr;*/
	}

	MonsterChaseGame* MonsterChaseGame::Create()
	{
		if (!instance_)
		{
			instance_ = new MonsterChaseGame();
		}
		return instance_;
	}

	MonsterChaseGame* MonsterChaseGame::GetInstance()
	{
		return instance_;
	}

	StrongPtr<GameObject> MonsterChaseGame::GetPlayer()
	{
		return player_;
	}

	void MonsterChaseGame::Destroy()
	{
		/*if (instance_) {
			delete instance_;
			instance_ = nullptr;
		}*/
	}

	void MonsterChaseGame::Initialize()
	{
		using namespace std::placeholders;
		const char* CustomQueueName = "GameObjectLoader";
		Engine::HashedString QueueName = Engine::JobSystem::CreateQueue(CustomQueueName, 1);

		Engine::JobSystem::RunJob(QueueName, std::bind(JsonGameObjectUtils::CreateGameObjectFromJson, "test data file - Copy.json"));
		Engine::JobSystem::RunJob(QueueName, std::bind(JsonGameObjectUtils::CreateGameObjectFromJson, "test data file.json"));


		//player_ = JsonGameObjectUtils::CreateGameObjectFromJson("test data file.json");
		//GameObject::CheckForNewGameObjects();

	}

	void MonsterChaseGame::Update()
	{
		//get the input reader associated with Engine
		InputReader* inputReaderInstance = InputReader::GetInstance();
		PhysicsSystem* physicsSystemInstance = PhysicsSystem::GetInstance();
		float speed = 0.2f;

		for each (StrongPtr<PhysicsObject> po in physicsSystemInstance->GetPhysicsObjects())
		{
			//this is temporary solution, gotta fix later
			if (po->GetControllable()) {
				if (inputReaderInstance->isKey_W_Down)
					po->ApplyForce(Vector2(0.0f, speed));
				if (inputReaderInstance->isKey_S_Down)
					po->ApplyForce(Vector2(0.0f, -speed));
				if (inputReaderInstance->isKey_D_Down)
					po->ApplyForce(Vector2(speed, 0.0f));
				if (inputReaderInstance->isKey_A_Down)
					po->ApplyForce(Vector2(-speed, 0.0f));
			}
		}

		//check if quit
		if (inputReaderInstance->isKey_Q_Down) {
			quitMonsterChaseGame = true;

			//const size_t	lenBuffer = 65;
			//char			Buffer[lenBuffer];
			//sprintf_s(Buffer, lenBuffer, "Q went down \n");
			//OutputDebugStringA(Buffer);
		}

	}

}




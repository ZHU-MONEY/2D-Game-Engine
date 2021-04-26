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
		target1_ = nullptr;
		target2_ = nullptr;
		target3_ = nullptr;
		winScene_ = nullptr;
		loseScene_ = nullptr;
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

	StrongPtr<GameObject> MonsterChaseGame::GetTarget1()
	{
		return target1_;
	}

	StrongPtr<GameObject> MonsterChaseGame::GetTarget2()
	{
		return target2_;
	}

	StrongPtr<GameObject> MonsterChaseGame::GetTarget3()
	{
		return target3_;
	}

	void MonsterChaseGame::RespondToCollision(GameObject* go1, GameObject* go2)
	{
		//if (Game::MonsterChaseGame::GetInstance()->GetPlayer().GetObjectPtr() == go1 ||
		//	Game::MonsterChaseGame::GetInstance()->GetPlayer().GetObjectPtr() == go2) {
		//	player_->SetIsActive(false);
		//}

		//if (player_.GetObjectPtr() == go1 ||
		//	player_.GetObjectPtr() == go2) {
		//	player_->SetIsActive(false);
		//}


		//if (Game::MonsterChaseGame::GetInstance()->GetPlayer().GetObjectPtr() == this) {
		//	return;
		//}

		//if (Game::MonsterChaseGame::GetInstance()->GetTarget1().GetObjectPtr() == this ||
		//	Game::MonsterChaseGame::GetInstance()->GetTarget2().GetObjectPtr() == this ||
		//	Game::MonsterChaseGame::GetInstance()->GetTarget3().GetObjectPtr() == this) {
		//	this->SetIsActive(false);
		//}
		//this is a very broken way of getting things done
		//if (this->isStatic_) {
		//	if (other->GetIsStatic())
		//		return;
		//	else if (other == Game::MonsterChaseGame::GetInstance()->GetPlayer().GetObjectPtr())
		//		other->SetIsActive(false);
		//}
	}

	void MonsterChaseGame::Destroy()
	{
		if (instance_) {
			delete instance_;
			instance_ = nullptr;
		}
	}

	void MonsterChaseGame::Initialize()
	{
		using namespace std::placeholders;
		//Engine::HashedString QueueName = Engine::JobSystem::CreateQueue("GameObjectLoader", 1);

		//Engine::JobSystem::RunJob(QueueName, std::bind(JsonGameObjectUtils::CreateGameObjectFromJson, "Game/GameObjects/center.json"));
		//Engine::JobSystem::RunJob(QueueName, std::bind(JsonGameObjectUtils::CreateGameObjectFromJson, "Game/GameObjects/center2.json"));
		//Engine::JobSystem::RunJob(QueueName, std::bind(JsonGameObjectUtils::CreateGameObjectFromJson, "Game/GameObjects/wall left.json"));
		//Engine::JobSystem::RunJob(QueueName, std::bind(JsonGameObjectUtils::CreateGameObjectFromJson, "Game/GameObjects/wall right.json"));
		//Engine::JobSystem::RunJob(QueueName, std::bind(JsonGameObjectUtils::CreateGameObjectFromJson, "Game/GameObjects/wall top.json"));
		//Engine::JobSystem::RunJob(QueueName, std::bind(JsonGameObjectUtils::CreateGameObjectFromJson, "Game/GameObjects/player.json"));




		JsonGameObjectUtils::CreateGameObjectFromJson( "Game/GameObjects/wall left.json");
		JsonGameObjectUtils::CreateGameObjectFromJson( "Game/GameObjects/wall right.json");
		JsonGameObjectUtils::CreateGameObjectFromJson("Game/GameObjects/wall top.json");
		JsonGameObjectUtils::CreateGameObjectFromJson("Game/GameObjects/wall bottom.json");

		winScene_ = JsonGameObjectUtils::CreateGameObjectFromJson("Game/GameObjects/you won.json");
		loseScene_ = JsonGameObjectUtils::CreateGameObjectFromJson("Game/GameObjects/you lost.json");
		player_ = JsonGameObjectUtils::CreateGameObjectFromJson("Game/GameObjects/player.json");
		target1_ = JsonGameObjectUtils::CreateGameObjectFromJson("Game/GameObjects/target1.json");
		target2_ = JsonGameObjectUtils::CreateGameObjectFromJson("Game/GameObjects/target2.json");
		target3_ = JsonGameObjectUtils::CreateGameObjectFromJson("Game/GameObjects/target3.json");
		winScene_.GetObjectPtr()->SetIsActive(false);
		loseScene_.GetObjectPtr()->SetIsActive(false);

		GameObject::CheckForNewGameObjects();

	}

	void MonsterChaseGame::Update()
	{
		//if win or lose game, wait 3 sec and quit game
		if (loseScene_.GetObjectPtr()->GetIsActive()|| winScene_.GetObjectPtr()->GetIsActive()) {
			Sleep(3000);
			quitMonsterChaseGame = true;
		}

		//get the input reader associated with Engine
		InputReader* inputReaderInstance = InputReader::GetInstance();
		PhysicsSystem* physicsSystemInstance = PhysicsSystem::GetInstance();

		if (!player_.GetObjectPtr()->GetIsActive()) {
			loseScene_.GetObjectPtr()->SetIsActive(true);
		}

		if (!target1_.GetObjectPtr()->GetIsActive() && !target2_.GetObjectPtr()->GetIsActive() && !target3_.GetObjectPtr()->GetIsActive()) {
			winScene_.GetObjectPtr()->SetIsActive(true);
		}


		//movement
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

		}

	}

}




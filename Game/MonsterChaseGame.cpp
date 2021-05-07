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
		char			Buffer[65];
		sprintf_s(Buffer, 65, "Game initialized \n");
		OutputDebugStringA(Buffer);
		return true;
	}

	void Shutdown()
	{
		MonsterChaseGame::Destroy();
		char			Buffer[65];
		sprintf_s(Buffer, 65, "Game shutdown \n");
		OutputDebugStringA(Buffer);
	}

	// static member initialization
	MonsterChaseGame* MonsterChaseGame::instance_ = nullptr;
	bool MonsterChaseGame::quitMonsterChaseGame = false;
	bool MonsterChaseGame::movingFireNeedMoveRight = true;
	MonsterChaseGame::MonsterChaseGame()
	{
		player_ = nullptr;
		target1_ = nullptr;
		target2_ = nullptr;
		target3_ = nullptr;
		fire1_ = nullptr;
		fire2_ = nullptr;
		fire3_ = nullptr;
		fire4_ = nullptr;
		movingFire1_ = nullptr;
		movingFire2_ = nullptr;
		winScene_ = nullptr;
		loseScene_ = nullptr;
	}

	MonsterChaseGame::~MonsterChaseGame()
	{
	}

	MonsterChaseGame* MonsterChaseGame::Create()
	{
		if (!instance_)
		{
			instance_ = new MonsterChaseGame();
		}
		char			Buffer[65];
		sprintf_s(Buffer, 65, "Game created \n");
		OutputDebugStringA(Buffer);
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

		//if player collides with target
		if (			
			(player_.GetObjectPtr() == go1 && (target1_.GetObjectPtr() == go2 || target2_.GetObjectPtr() == go2 || target3_.GetObjectPtr() == go2)) ||
			(player_.GetObjectPtr() == go2 && (target1_.GetObjectPtr() == go1 || target2_.GetObjectPtr() == go1 || target3_.GetObjectPtr() == go1))			
			)
		{
			if (player_.GetObjectPtr() == go1) {
				go2->SetIsActive(false);
			}
			if (player_.GetObjectPtr() == go2) {
				go1->SetIsActive(false);
			}
		}

		//if player collides with fire
		if (
			(player_.GetObjectPtr() == go1 && (fire1_.GetObjectPtr() == go2 || fire2_.GetObjectPtr() == go2 || fire3_.GetObjectPtr() == go2 || fire4_.GetObjectPtr() == go2 || movingFire1_.GetObjectPtr() == go2 || movingFire2_.GetObjectPtr() == go2)) ||
			(player_.GetObjectPtr() == go2 && (fire1_.GetObjectPtr() == go1 || fire2_.GetObjectPtr() == go1 || fire3_.GetObjectPtr() == go1 || fire4_.GetObjectPtr() == go1 || movingFire1_.GetObjectPtr() == go1 || movingFire2_.GetObjectPtr() == go1))
			)
		{
			if (player_.GetObjectPtr() == go1) {
				go1->SetIsActive(false);
			}
			if (player_.GetObjectPtr() == go2) {
				go2->SetIsActive(false);
			}
		}
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

		//loading assets async, this can cause some racing condition some time, so it is not being used

		/*using namespace std::placeholders;
		Engine::HashedString QueueName = Engine::JobSystem::CreateQueue("GameObjectLoader", 1);

		Engine::JobSystem::RunJob(QueueName, std::bind(JsonGameObjectUtils::CreateGameObjectFromJson, "Game/GameObjects/center.json"));
		Engine::JobSystem::RunJob(QueueName, std::bind(JsonGameObjectUtils::CreateGameObjectFromJson, "Game/GameObjects/center2.json"));
		Engine::JobSystem::RunJob(QueueName, std::bind(JsonGameObjectUtils::CreateGameObjectFromJson, "Game/GameObjects/wall left.json"));
		Engine::JobSystem::RunJob(QueueName, std::bind(JsonGameObjectUtils::CreateGameObjectFromJson, "Game/GameObjects/wall right.json"));
		Engine::JobSystem::RunJob(QueueName, std::bind(JsonGameObjectUtils::CreateGameObjectFromJson, "Game/GameObjects/wall top.json"));
		Engine::JobSystem::RunJob(QueueName, std::bind(JsonGameObjectUtils::CreateGameObjectFromJson, "Game/GameObjects/player.json"));**/




		fire1_ = JsonGameObjectUtils::CreateGameObjectFromJson( "Game/GameObjects/wall left.json");
		fire2_ = JsonGameObjectUtils::CreateGameObjectFromJson( "Game/GameObjects/wall right.json");
		fire3_ = JsonGameObjectUtils::CreateGameObjectFromJson("Game/GameObjects/wall top.json");
		fire4_ = JsonGameObjectUtils::CreateGameObjectFromJson("Game/GameObjects/wall bottom.json");

		movingFire1_ = JsonGameObjectUtils::CreateGameObjectFromJson("Game/GameObjects/moving fire 1.json");
		movingFire2_ = JsonGameObjectUtils::CreateGameObjectFromJson("Game/GameObjects/moving fire 2.json");

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

#pragma region movingFire1
		if (movingFire1_->GetPosition().x()== 500.0f) {
			movingFireNeedMoveRight = false;
		}
		if (movingFire1_->GetPosition().x()== -500.0f) {
			movingFireNeedMoveRight = true;
		}
		if (movingFireNeedMoveRight) {			
			movingFire1_->SetPosition(Vector2(movingFire1_->GetPosition().x() + 0.5f, movingFire1_->GetPosition().y()));
		}
		else if(!movingFireNeedMoveRight){
			movingFire1_->SetPosition(Vector2(movingFire1_->GetPosition().x() - 0.5f, movingFire1_->GetPosition().y()));
		}
#pragma endregion

#pragma region movingFire2
		if (!movingFireNeedMoveRight) {
			movingFire2_->SetPosition(Vector2(movingFire2_->GetPosition().x() + 0.5f, movingFire2_->GetPosition().y()));
		}
		else if (movingFireNeedMoveRight) {
			movingFire2_->SetPosition(Vector2(movingFire2_->GetPosition().x() - 0.5f, movingFire2_->GetPosition().y()));
		}
#pragma endregion

		//check if quit
		if (inputReaderInstance->isKey_Q_Down) {
			quitMonsterChaseGame = true;

		}

	}

}




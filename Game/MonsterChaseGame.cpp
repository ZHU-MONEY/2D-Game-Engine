#include "MonsterChaseGame.h"
#include "Engine/Time/TimeUtils.Win.cpp"
#include "Engine/Time/TimeUtils.h"
#include <Engine\Input\InputReader.h>
#include "Engine/Physics/PhysicsObject.h"
#include "Engine/Render/Renderer.h"
#include "Engine/GameObject/JsonGameObjectUtils.h"

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
		player_ = GameObject::Create();

		//physics part
		//PhysicsSystem* physicsSystemInstance = PhysicsSystem::GetInstance();
		//---PhysicsObject* po = new PhysicsObject(WeakPtr<GameObject>(player_), PhysicsObject::DEFAULT_MASS, PhysicsObject::DEFAULT_COEFFICIENT_DRAG);
		//physicsSystemInstance->AddPhysicsObject(po);

		//render part
		//Renderer* rendererInstance = Renderer::GetInstance();


		//---RenderableObject* ro = new RenderableObject(WeakPtr<GameObject>(player_), player_.GetObjectPtr()->GetSprite());
		//rendererInstance->AddRenderableObject(ro);

		//testing purpose
		//GLib::Sprite* sssss = EngineUtils::CreateSprite("data\\BadGuy.dds");
		//ro->SetSprite(sssss);

		player_ = JsonGameObjectUtils::CreateGameObjectFromJson("test data file.json");


	}

	void MonsterChaseGame::Update()
	{
		//get the input reader associated with Engine
		InputReader* inputReaderInstance = InputReader::GetInstance();
		PhysicsSystem* physicsSystemInstance = PhysicsSystem::GetInstance();
		float speed = 0.2f;

		for each (PhysicsObject * po in physicsSystemInstance->GetPhysicsObjects())
		{
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

}




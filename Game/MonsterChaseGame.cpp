#include "MonsterChaseGame.h"


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

	void AcceptKey(unsigned int i_VKeyID, bool bWentDown)
	{
#ifdef _DEBUG
		const size_t	lenBuffer = 65;
		char			Buffer[lenBuffer];

		//sprintf_s(Buffer, lenBuffer, "VKey %04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
		sprintf_s(Buffer, lenBuffer, "HAHAHAHAHAH  %s\n", MonsterChaseGame::isKey_A_Down ? "A is downFUCK" : "A is upFUCK");
		OutputDebugStringA(Buffer);
#endif // __DEBUG
		
		switch (i_VKeyID)
		{
			//W 57---hexadecimal   87---decimal
		case 87:
			MonsterChaseGame::isKey_W_Down = bWentDown;
			break;

			//A 41---hexadecimal	65---decimal
		case 65:
			MonsterChaseGame::isKey_A_Down = bWentDown;
			break;

			//S  53---hexadecimal   83---decimal
		case 83:
			MonsterChaseGame::isKey_S_Down = bWentDown;
			break;

			//D   44---hexadecimal  68---decimal
		case 68:
			MonsterChaseGame::isKey_D_Down = bWentDown;
			break;
		}
	}


	// static member initialization
	MonsterChaseGame* MonsterChaseGame::instance_ = nullptr;
	bool MonsterChaseGame::isKey_W_Down = false;
	bool MonsterChaseGame::isKey_A_Down = false;
	bool MonsterChaseGame::isKey_S_Down = false;
	bool MonsterChaseGame::isKey_D_Down = false;

	MonsterChaseGame::MonsterChaseGame()
	{
		player_ = nullptr;

		GLib::SetKeyStateChangeCallback(AcceptKey);

		//GLib::Sprite* pGoodGuy = EngineUtils::CreateSprite("data\\GoodGuy.dds");
		//player_ = new Actor("zhu", Vector2(0, 0));
		//player_->SetSprite(pGoodGuy);
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

	void MonsterChaseGame::Destroy()
	{
		/*if (instance_) {
			delete instance_;
			instance_ = nullptr;
		}*/
	}

	void MonsterChaseGame::Initialize()
	{
		//player_ = new Actor("zhu", Vector2(0, 0));
		player_ = new GameObject();

		PhysicsSystem::Create();
		physicsSystemInstance = PhysicsSystem::GetInstance();

		po_ = new PhysicsObject(player_, PhysicsObject::DEFAULT_MASS, PhysicsObject::DEFAULT_COEFFICIENT_DRAG);

		physicsSystemInstance->AddPhysicsObject(po_);
		
	}

	void MonsterChaseGame::Update()
	{

		//for debug
		const size_t	lenBuffer = 65;
		char			Buffer[lenBuffer];	
		sprintf_s(Buffer, lenBuffer, "HAHAHAHAHAH  %s\n", MonsterChaseGame::isKey_A_Down ? "A is down TRUE" : "A is up FALSE");
		OutputDebugStringA(Buffer);

		if (isKey_D_Down)
			po_->ApplyForce(Vector2(0.1f, 0.0f));
		if (isKey_A_Down)
			po_->ApplyForce(Vector2(-0.1f, 0.0f));

		physicsSystemInstance->Run(16.6f);

		/*Vector2 speed = Vector2(0.01f, 0);
		Vector2 speed2 = Vector2(-0.01f, 0);
		if (isKey_D_Down) {


			player_->Move(speed);
		}

		if (isKey_A_Down) {
			player_->Move(speed2);
		}*/

		bool quit = false;
		GLib::Service(quit);

		if (!quit)
		{
			Render();
		}
	}

	void MonsterChaseGame::Render()
	{
		// Tell GLib that we want to start rendering
		GLib::BeginRendering(DirectX::Colors::Blue);
		// Tell GLib that we want to render some sprites
		GLib::Sprites::BeginRendering();

		player_->Render();
		
		// Tell GLib we're done rendering sprites
		GLib::Sprites::EndRendering();
		// Tell GLib we're done rendering
		GLib::EndRendering();
	}
}

//Actor* MonsterChaseGame::GetPlayer()
//{
//	//return player_;
//}



#include "MonsterChaseGame.h"

//void AcceptKey(unsigned int i_VKeyID, bool bWentDown)
//{
//#ifdef _DEBUG
//	const size_t	lenBuffer = 65;
//	char			Buffer[lenBuffer];
//
//	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
//	OutputDebugStringA(Buffer);
//#endif // __DEBUG
//
//	switch (i_VKeyID)
//	{
//		//W
//	case 57:
//		MonsterChaseGame::isKey_W_Down = bWentDown;
//		break;
//		//A
//	case 41:
//		MonsterChaseGame::isKey_A_Down = bWentDown;
//		break;
//		//S
//	case 53:
//		MonsterChaseGame::isKey_S_Down = bWentDown;
//		break;
//		//D
//	case 44:
//		MonsterChaseGame::isKey_D_Down = bWentDown;
//		break;
//	}
//}
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

		//GLib::SetKeyStateChangeCallback(AcceptKey);

		//GLib::Sprite* pGoodGuy = EngineUtils::CreateSprite("data\\GoodGuy.dds");
		//player_ = new Actor("zhu", Vector2(0, 0));
		//player_->SetSprite(pGoodGuy);
	}

	MonsterChaseGame::~MonsterChaseGame()
	{
		delete player_;
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
		delete instance_;
	}

	void MonsterChaseGame::Initialize()
	{
		player_ = new Actor("zhu", Vector2(0, 0));
	}

	void MonsterChaseGame::Update()
	{
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



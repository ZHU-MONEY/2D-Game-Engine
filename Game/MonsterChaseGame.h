#pragma once
#include "Glib\GLib.h"
#include "Actor\Actor.h"
#include "Engine\EngineUtils.h"
#include <DirectXColors.h>
#include "Engine/GameObject/GameObject.h"
#include <Engine\Physics\PhysicsSystem.h>
#include "Engine/GameObject/StrongPtr.h"

namespace Game {

	static const  int GAME_HEIGHT = 800;
	static const int GAME_WIDTH = 1000;

	bool StartUp();
	void Shutdown();

	class MonsterChaseGame
	{
		StrongPtr<GameObject> player_;
		StrongPtr<GameObject> target1_;
		StrongPtr<GameObject> target2_;
		StrongPtr<GameObject> target3_;
		StrongPtr<GameObject> winScene_;
		StrongPtr<GameObject> loseScene_;
		MonsterChaseGame();
		~MonsterChaseGame();
		static MonsterChaseGame* instance_;

	public:	
		static MonsterChaseGame* Create();
		static MonsterChaseGame* GetInstance();
		StrongPtr<GameObject> GetPlayer();
		StrongPtr<GameObject> GetTarget1();
		StrongPtr<GameObject> GetTarget2();
		StrongPtr<GameObject> GetTarget3();
		static void Destroy();

		void Initialize();
		void Update();

		static bool quitMonsterChaseGame;
	};
}//end Game namespace

#pragma once
#ifndef MONSTER_CHASE_GAME_
#define MONSTER_CHASE_GAME_
#include "Glib\GLib.h"
#include "Actor\Actor.h"
#include "Engine\EngineUtils.h"
#include <DirectXColors.h>
#include "Engine/GameObject/GameObject.h"
#include <Engine\Physics\PhysicsSystem.h>
#include "Engine/GameObject/StrongPtr.h"

namespace Game {
	bool StartUp();
	void Shutdown();
	void AcceptKey(unsigned int i_VKeyID, bool bWentDown);

	class MonsterChaseGame
	{
		StrongPtr<GameObject> player_;
		MonsterChaseGame();
		~MonsterChaseGame();
		static MonsterChaseGame* instance_;

	public:	
		static MonsterChaseGame* Create();
		static MonsterChaseGame* GetInstance();
		StrongPtr<GameObject> GetPlayer();
		static void Destroy();

		void Initialize();
		void Update();
		void Render();

		static bool	isKey_W_Down;
		static bool isKey_A_Down;
		static bool	isKey_S_Down;
		static bool	isKey_D_Down;		
	};
}//end Game namespace
#endif
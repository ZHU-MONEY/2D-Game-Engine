#pragma warning( disable : 28251 )
#include <stdlib.h>


#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <DirectXColors.h>

#include "Containers/List.h"
#include "Console/ConsolePrint.h"
#include "Glib/GLib.h"
#include "Engine\EngineUtils.h"
#include "Game/MonsterChaseGame.h"
#include <iostream>
#include "Engine/Time/TimeUtils.h"
#include "Engine/Engine.h"

#include "Engine/GameObject/WeakPtr.h"
#include "Engine/Physics/PhysicsSystem.h"
#include "Engine/Render/Renderer.h"

#include "Engine/Input/InputReader.h"


int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (Engine::StartUp())
	{
		// IMPORTANT: first we need to initialize GLib
		bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "MonsterChaseGame", -1, Game::GAME_WIDTH, Game::GAME_HEIGHT, true);
		if (bSuccess)
		{
			Game::StartUp();
			Game::MonsterChaseGame* MC = Game::MonsterChaseGame::GetInstance();

			while (!MC->quitMonsterChaseGame) {
				GLib::Service(MC->quitMonsterChaseGame);
				Engine::Run();
				MC->Update();
			}

			Game::Shutdown();
			// IMPORTANT:  Tell GLib to shutdown, releasing resources.
			GLib::Shutdown();
			Engine::Shutdown();
		}
	}
}



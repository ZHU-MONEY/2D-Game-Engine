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

#include "Actor/Actor.h"
#include "Containers/List.h"
#include "Console/ConsolePrint.h"
#include "Glib/GLib.h"
#include "Engine\EngineUtils.h"
#include "Game/MonsterChaseGame.h"
#include <iostream>
#include "Engine/Time/TimeUtils.h"
#include "Game/PlayerController.h"
#include "Engine/Engine.h"
//#include "Engine/Time/TimeUtils.Win.cpp"
#include "Engine/GameObject/WeakPtr.h"
#include "Engine/Physics/PhysicsSystem.h"
#include "Engine/Render/Renderer.h"

// create a random number in a range
// not a very robust solution tends to bias toward the low end
template<typename T>
T RandInRange(T i_Min, T i_Max)
{
	static bool bInitialized = false;

	// if we haven't seeded he random number generator do so
	if (!bInitialized)
	{
		srand(static_cast<unsigned int>(time(NULL)));
		bInitialized = true;
	}

	return rand() % (i_Max - i_Min + 1) + i_Min;
}

// create 2D with it's x and y values in a given range
Vector2 RandomVector2(int i_Min, int i_Max)
{
	return Vector2(RandInRange(i_Min, i_Max), RandInRange(i_Min, i_Max));
}

char GetUserInput()
{
	//#define FAKE_USER_INPUT
#ifdef FAKE_USER_INPUT
	return 'd';
#else
	return  _getch();
#endif
}

//void RunGame()
//{
//
//#if defined(_DEBUG) && defined(ROBUST_MEMORY_CHECKS)
//	// Get current flag
//	int CrtDbgFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
//	// Turn on leak-checking bit.
//	CrtDbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;
//	// Set flag to the new value.
//	_CrtSetDbgFlag(CrtDbgFlags);
//
//	// _CrtSetBreakAlloc(88);
//#endif
//
//	// dimension of the play grid
//	const int		GridDim = 100;
//
//	// a buffer for getting input from the users
//	const size_t	lenInput = 128;
//	char			Input[lenInput];
//
//	printf("Welcome to MonsterChase!\n\n");
//
//	// ask the user how many monsters they'd like to start with (min 1)
//	unsigned int numMonsters = 0;
//
//	do
//	{
//		printf("How many monsters to start: ");
//		gets_s(Input, lenInput);
//
//		numMonsters = atoi(Input);
//
//		if (numMonsters == 0)
//			printf("Bad input. Please enter an integer greater than 0.");
//
//	} while (numMonsters == 0);
//
//	printf("\n");
//
//	// create our list of monsters
//	struct _LinkNode<Actor>* pMonsters = nullptr;
//
//	for (unsigned int i = 0; i < numMonsters; i++)
//	{
//		while (1)
//		{
//			printf("Enter a name for monster %d: ", i);
//			gets_s(Input, lenInput);
//
//			if (strlen(Input))
//			{
//				pMonsters = new struct _LinkNode<Actor>(Actor(Input, RandomVector2(-GridDim, GridDim)), pMonsters);
//				break;
//			}
//			else
//			{
//				printf("Empty name not allowed.");
//			}
//		}
//
//	}
//
//	printf("\n");
//
//	// get a name for the player
//	while (1)
//	{
//		printf("Enter a name for the player: ");
//		gets_s(Input, lenInput);
//
//		if (strlen(Input))
//		{
//			break;
//		}
//		else
//		{
//			printf("Empty name not allowed.");
//		}
//	}
//
//	printf("\n");
//
//	// create the player
//	Actor Player(Input, Vector2(0, 0));
//
//	// loop until we quit by breaking out
//	while (1)
//	{
//		// show all the monster locations.
//		printf("Monsters:\n");
//		struct _LinkNode<Actor>* pMonster = pMonsters;
//
//		while (pMonster)
//		{
//			pMonster->Item.Print();
//
//			pMonster->Item.Move(RandomVector2(-2, 2));
//
//			pMonster = pMonster->pNext;
//		}
//		printf("\n");
//
//		// show the player location.
//		printf("Player:\n");
//		Player.Print();
//		printf("\n");
//
//		// 10% chance of a monster dying.
//		// if not 10% chance of a new monster being created.
//		if (RandInRange(0, 10) == 1)
//		{
//			static int		newMonsterNumber = 0;
//
//			const int		lenName = 16;
//			char			Name[lenName];
//
//			sprintf_s(Name, lenName, "Newbie %d", newMonsterNumber++);
//
//			DEBUG_PRINT("Creating a new monster named %s.", Name);
//			pMonsters = new struct _LinkNode<Actor>(Actor(Name, RandomVector2(-GridDim, GridDim)), pMonsters);
//		}
//		else if (pMonsters && (RandInRange(0, 10) == 1))
//		{
//			// pick a random guy to die. sorry guy :(
//			int DeadGuy = RandInRange(0, Count(pMonsters) - 1);
//
//			DEBUG_PRINT("Destroying monster named %s.", GetAt(pMonsters, DeadGuy)->Item.Name());
//			RemoveAt(pMonsters, DeadGuy);
//		}
//
//		// quit flag.
//		bool bQuit = false;
//
//		// loop until we get a valid input from player.
//		while (1)
//		{
//			bool bValidInput = true;
//
//			printf("Press A to move left, D to move right, W to move up, S to move down or Q to quit");
//			char input = GetUserInput();
//
//			switch (input)
//			{
//			case 'a':
//			case 'A':
//				Player.Move(Vector2(-1, 0));
//				break;
//			case 'd':
//			case 'D':
//				Player.Move(Vector2(1, 0));
//				break;
//			case 'w':
//			case 'W':
//				Player.Move(Vector2(0, 1));
//				break;
//			case 's':
//			case 'S':
//				Player.Move(Vector2(0, -1));
//				break;
//			case 'q':
//			case 'Q':
//				bQuit = true;
//				break;
//			default:
//				printf("Unknown input.\n");
//				bValidInput = false;
//				break;
//			}
//
//			if (bValidInput)
//				break;
//		}
//
//		printf("\n\n");
//		// if user asked to quit break out.
//		if (bQuit)
//			break;
//	}
//
//	// free up our monster list.
//	while (pMonsters)
//		RemoveAt(pMonsters, 0);
//
//	printf("Thanks for playing.\n");
//}

void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	//sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
	//std::cout << "THE KEY YOU PRESSED IS-----" << i_VKeyID << std::endl;

#endif // __DEBUG
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{

	if (Engine::StartUp())
	{
		// IMPORTANT: first we need to initialize GLib
		bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "MonsterChaseGame", -1, 1000, 800, true);
		if (bSuccess)
		{
			Game::StartUp();
			Game::MonsterChaseGame* MC = Game::MonsterChaseGame::GetInstance();

			PhysicsObject* po = new PhysicsObject(WeakPtr<GameObject>(MC->GetPlayer()), PhysicsObject::DEFAULT_MASS,PhysicsObject::DEFAULT_COEFFICIENT_DRAG);
			//can probably add this code into the PhysicsObject constructor
			PhysicsSystem* physicsSystemInstance = PhysicsSystem::GetInstance();
			physicsSystemInstance->AddPhysicsObject(po);


			//render part 
			Renderer* rendererInstance = Renderer::GetInstance();

			//get the image
			GLib::Sprite* sssss = EngineUtils::CreateSprite("data\\BadGuy.dds");

			//RenderableObject* ro = new RenderableObject(WeakPtr<GameObject>(MC->GetPlayer()), MC->GetPlayer().GetObjectPtr()->GetSprite());

			RenderableObject* ro = new RenderableObject(WeakPtr<GameObject>(MC->GetPlayer()), sssss);
			
			rendererInstance->AddRenderableObject(ro);

			

			//render part 
			//-----Renderer* rendererInstance = Renderer::GetInstance();

			/*RenderableObject* ro = new RenderableObject(WeakPtr<GameObject>(MC->GetPlayer()), MC->GetPlayer().GetObjectPtr()->GetSprite());*/

			//----RenderableObject* ro = new RenderableObject(WeakPtr<GameObject>(MC->GetPlayer()), sssss);
			
			//----rendererInstance->AddRenderableObject(ro);



			
			bool quit = false;
			while (!quit) {


				float speed = 0.2f;
				if (MC->isKey_W_Down)
					po->ApplyForce(Vector2(0.0f, speed));
				if (MC->isKey_S_Down)
					po->ApplyForce(Vector2(0.0f, -speed));
				if (MC->isKey_D_Down)
					po->ApplyForce(Vector2(speed, 0.0f));
				if (MC->isKey_A_Down)
					po->ApplyForce(Vector2(-speed, 0.0f));

				Engine::Run();
				//MC->Update();
			}

			MC->Destroy();
			// IMPORTANT:  Tell GLib to shutdown, releasing resources.
			GLib::Shutdown();
		}
	}

	//#if defined _DEBUG
	_CrtDumpMemoryLeaks();
	//#endif // _DEBUG

}



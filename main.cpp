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
Engine::Math::Vector2 RandomVector2(int i_Min, int i_Max)
{
	return Engine::Math::Vector2(RandInRange(i_Min, i_Max), RandInRange(i_Min, i_Max));
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

void RunGame()
{
	using namespace Engine::Math;

#if defined(_DEBUG) && defined(ROBUST_MEMORY_CHECKS)
	// Get current flag
	int CrtDbgFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	// Turn on leak-checking bit.
	CrtDbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;
	// Set flag to the new value.
	_CrtSetDbgFlag(CrtDbgFlags);

	// _CrtSetBreakAlloc(88);
#endif

	// dimension of the play grid
	const int		GridDim = 100;

	// a buffer for getting input from the users
	const size_t	lenInput = 128;
	char			Input[lenInput];

	printf("Welcome to MonsterChase!\n\n");

	// ask the user how many monsters they'd like to start with (min 1)
	unsigned int numMonsters = 0;

	do
	{
		printf("How many monsters to start: ");
		gets_s(Input, lenInput);

		numMonsters = atoi(Input);

		if (numMonsters == 0)
			printf("Bad input. Please enter an integer greater than 0.");

	} while (numMonsters == 0);

	printf("\n");

	// create our list of monsters
	struct _LinkNode<Actor>* pMonsters = nullptr;

	for (unsigned int i = 0; i < numMonsters; i++)
	{
		while (1)
		{
			printf("Enter a name for monster %d: ", i);
			gets_s(Input, lenInput);

			if (strlen(Input))
			{
				pMonsters = new struct _LinkNode<Actor>(Actor(Input, RandomVector2(-GridDim, GridDim)), pMonsters);
				break;
			}
			else
			{
				printf("Empty name not allowed.");
			}
		}

	}

	printf("\n");

	// get a name for the player
	while (1)
	{
		printf("Enter a name for the player: ");
		gets_s(Input, lenInput);

		if (strlen(Input))
		{
			break;
		}
		else
		{
			printf("Empty name not allowed.");
		}
	}

	printf("\n");

	// create the player
	Actor Player(Input, Vector2(0, 0));

	// loop until we quit by breaking out
	while (1)
	{
		// show all the monster locations.
		printf("Monsters:\n");
		struct _LinkNode<Actor>* pMonster = pMonsters;

		while (pMonster)
		{
			pMonster->Item.Output();

			pMonster->Item.Move(RandomVector2(-2, 2));

			pMonster = pMonster->pNext;
		}
		printf("\n");

		// show the player location.
		printf("Player:\n");
		Player.Output();
		printf("\n");

		// 10% chance of a monster dying.
		// if not 10% chance of a new monster being created.
		if (RandInRange(0, 10) == 1)
		{
			static int		newMonsterNumber = 0;

			const int		lenName = 16;
			char			Name[lenName];

			sprintf_s(Name, lenName, "Newbie %d", newMonsterNumber++);

			DEBUG_PRINT("Creating a new monster named %s.", Name);
			pMonsters = new struct _LinkNode<Actor>(Actor(Name, RandomVector2(-GridDim, GridDim)), pMonsters);
		}
		else if (pMonsters && (RandInRange(0, 10) == 1))
		{
			// pick a random guy to die. sorry guy :(
			int DeadGuy = RandInRange(0, Count(pMonsters) - 1);

			DEBUG_PRINT("Destroying monster named %s.", GetAt(pMonsters, DeadGuy)->Item.Name());
			RemoveAt(pMonsters, DeadGuy);
		}

		// quit flag.
		bool bQuit = false;

		// loop until we get a valid input from player.
		while (1)
		{
			bool bValidInput = true;

			printf("Press A to move left, D to move right, W to move up, S to move down or Q to quit");
			char input = GetUserInput();

			switch (input)
			{
			case 'a':
			case 'A':
				Player.Move(Vector2(-1, 0));
				break;
			case 'd':
			case 'D':
				Player.Move(Vector2(1, 0));
				break;
			case 'w':
			case 'W':
				Player.Move(Vector2(0, 1));
				break;
			case 's':
			case 'S':
				Player.Move(Vector2(0, -1));
				break;
			case 'q':
			case 'Q':
				bQuit = true;
				break;
			default:
				printf("Unknown input.\n");
				bValidInput = false;
				break;
			}

			if (bValidInput)
				break;
		}

		printf("\n\n");
		// if user asked to quit break out.
		if (bQuit)
			break;
	}

	// free up our monster list.
	while (pMonsters)
		RemoveAt(pMonsters, 0);

	printf("Thanks for playing.\n");
}

//console main

//int main()
//{
//	RunGame();
//
//#ifdef _DEBUG	
//	_CrtDumpMemoryLeaks();
//#endif // _DEBUG	
//
//	return 0;
//}


void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG
}

void* LoadFile(const char* i_pFilename, size_t& o_sizeFile)
{
	assert(i_pFilename != NULL);

	FILE* pFile = NULL;

	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
	if (fopenError != 0)
		return NULL;

	assert(pFile != NULL);

	int FileIOError = fseek(pFile, 0, SEEK_END);
	assert(FileIOError == 0);

	long FileSize = ftell(pFile);
	assert(FileSize >= 0);

	FileIOError = fseek(pFile, 0, SEEK_SET);
	assert(FileIOError == 0);

	uint8_t* pBuffer = new uint8_t[FileSize];
	assert(pBuffer);

	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
	assert(FileRead == FileSize);

	fclose(pFile);

	o_sizeFile = FileSize;

	return pBuffer;
}

GLib::Sprite* CreateSprite(const char* i_pFilename)
{
	assert(i_pFilename);

	size_t sizeTextureFile = 0;

	// Load the source file (texture data)
	void* pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
	GLib::Texture* pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

	// exit if something didn't work
	// probably need some debug logging in here!!!!
	if (pTextureFile)
		delete[] pTextureFile;

	if (pTexture == nullptr)
		return nullptr;

	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;

	// Get the dimensions of the texture. We'll use this to determine how big it is on screen
	bool result = GLib::GetDimensions(*pTexture, width, height, depth);
	assert(result == true);
	assert((width > 0) && (height > 0));

	// Define the sprite edges
	GLib::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
	GLib::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
	GLib::RGBA							Color = { 255, 255, 255, 255 };

	// Create the sprite
	GLib::Sprite* pSprite = GLib::CreateSprite(Edges, 0.1f, Color, UVs, pTexture);

	// release our reference on the Texture
	GLib::Release(pTexture);

	return pSprite;
}


int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600, true);
	if (bSuccess)
	{
		// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
		GLib::SetKeyStateChangeCallback(TestKeyCallback);

		Actor Player("asdasd", Engine::Math::Vector2(0, 0));

		GLib::Sprite* pGoodGuy = CreateSprite("data\\GoodGuy.dds");
		Player.SetSprite(pGoodGuy);

		// Create a couple of sprites using our own helper routine CreateSprite
		//GLib::Sprite* pGoodGuy = CreateSprite("data\\GoodGuy.dds");
		//GLib::Sprite* pBadGuy = CreateSprite("data\\BadGuy.dds");

		bool bQuit = false;

		do
		{
			// IMPORTANT: We need to let GLib do it's thing. 
			GLib::Service(bQuit);

			if (!bQuit)
			{
				// IMPORTANT: Tell GLib that we want to start rendering
				GLib::BeginRendering(DirectX::Colors::Blue);
				// Tell GLib that we want to render some sprites
				GLib::Sprites::BeginRendering();

				if (Player.GetSprite())
				{
					static float			moveDist = .01f;
					static float			moveDir = moveDist;

					static GLib::Point2D	Offset = { -180.0f, -100.0f };

					if (Offset.x < -220.0f)
						moveDir = moveDist;
					else if (Offset.x > -140.0f)
						moveDir = -moveDist;

					Offset.x += moveDir;

					// Tell GLib to render this sprite at our calculated location
					GLib::Render(*(Player.GetSprite()), Offset, 0.0f, 0.0f);
				}
				//if (pBadGuy)
				//{
				//	static float			moveDist = .02f;
				//	static float			moveDir = -moveDist;

				//	static GLib::Point2D	Offset = { 180.0f, -100.0f };

				//	if (Offset.x > 200.0f)
				//		moveDir = -moveDist;
				//	else if (Offset.x < 160.0f)
				//		moveDir = moveDist;

				//	Offset.x += moveDir;

				//	// Tell GLib to render this sprite at our calculated location
				//	GLib::Render(*pBadGuy, Offset, 0.0f, 0.0f);
				//}

				// Tell GLib we're done rendering sprites
				GLib::Sprites::EndRendering();
				// IMPORTANT: Tell GLib we're done rendering
				GLib::EndRendering();
			}
		} while (bQuit == false);

		if (Player.GetSprite())
			GLib::Release(pGoodGuy);
		//if (pBadGuy)
		//	GLib::Release(pBadGuy);

		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

}



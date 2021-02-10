#pragma once
#ifndef MONSTER_CHASE_GAME_
#define MONSTER_CHASE_GAME_
#include "Glib\GLib.h"
#include "Actor\Actor.h"
#include "Engine\EngineUtils.h"
using namespace Engine::Math;
class MonsterChaseGame
{
private:
	Actor* player_;
public:
	MonsterChaseGame();
	~MonsterChaseGame();
	Actor* GetPlayer();
};
#endif
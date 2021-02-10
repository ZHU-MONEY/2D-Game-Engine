#include "MonsterChaseGame.h"

MonsterChaseGame::MonsterChaseGame()
{
	GLib::Sprite* pGoodGuy = EngineUtils::CreateSprite("data\\GoodGuy.dds");
	player_ = new Actor("zhu", Vector2(0, 0));
	player_->SetSprite(pGoodGuy);
}

MonsterChaseGame::~MonsterChaseGame()
{
	delete player_;
}

Actor* MonsterChaseGame::GetPlayer()
{
	return player_;
}

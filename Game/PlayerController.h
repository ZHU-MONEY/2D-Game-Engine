#pragma once
#include "Engine/Physics/PhysicsObject.h"
#include "Engine/Math/Vector2.h"
#include "Game/MonsterChaseGame.h"
class PlayerController
{
public:
	static const float DEFAULT_MOVING_FORCE;

	PlayerController();
	PlayerController(PhysicsObject* po, Game::MonsterChaseGame* MC);
	~PlayerController();

	void Move();
private:
	PhysicsObject* po_;
	Game::MonsterChaseGame* MC_;
};

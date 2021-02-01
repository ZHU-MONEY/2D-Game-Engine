#pragma once

#include "Math\Vector2.h"

class Actor
{
public:
	Actor(const char * i_pName, const Engine::Math::Vector2 & i_InitialPosition);
	~Actor();

	Actor(const Actor & i_Other);
	Actor & operator=(const Actor & i_Other);

	const char * Name() const { return pName; }
	void Move(const Engine::Math::Vector2 & i_Movement);
	void Output() const;

private:
	char *							pName;
	Engine::Math::Vector2			Position;
};


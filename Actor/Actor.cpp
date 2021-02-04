#include "Actor.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Console/ConsolePrint.h"


Actor::Actor(const char * i_pName, const Engine::Math::Vector2 & i_InitialPosition) :
	pName(_strdup(i_pName ? i_pName : "Unnamed")),
	Position(i_InitialPosition)

{
#ifdef _DEBUG_ACTOR_CONSTRUCTORS
	DEBUG_PRINT("Creating actor named %s using standard constructor.", pName ? pName : "Unnamed" );
#endif // _DEBUG_ACTOR_CONSTRUCTORS
}

Actor::Actor(const Actor & i_Other) :
	pName(i_Other.pName ? _strdup(i_Other.pName) : nullptr),
	Position(i_Other.Position)
{
#ifdef _DEBUG_ACTOR_CONSTRUCTORS
	DEBUG_PRINT("Creating actor named %s using copy constructor.", pName ? pName : "Unnamed");
#endif // _DEBUG_ACTOR_CONSTRUCTORS
}

Actor::~Actor()
{
	if (pName)
		free(pName);
}

Actor & Actor::operator=(const Actor & i_Other)
{
#ifdef _DEBUG_ACTOR_CONSTRUCTORS
	DEBUG_PRINT("Reassigning actor named %s to %s using assignment operator.", pName ? pName : "Unnamed", i_Other.pName ? i_Other.pName : "Unnamed");
#endif // _DEBUG_ACTOR_CONSTRUCTORS

	if (pName)
		free(pName);
	
	pName = i_Other.pName ? _strdup(i_Other.pName) : nullptr;
	Position = i_Other.Position;

	return *this;
}

void Actor::Move(const Engine::Math::Vector2 & i_Movement)
{
	Position += i_Movement;
}

void Actor::Output() const
{
	assert(pName);
	printf("%s is at [%4d,%4d]\n", pName, Position.x(), Position.y());
}

void Actor::SetSprite(GLib::Sprite* s)
{
	pSprite = s;
}

GLib::Sprite* Actor::GetSprite()
{
	return pSprite;
}


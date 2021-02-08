#include "Actor.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Console/ConsolePrint.h"


Actor::Actor(const char * name, const Engine::Math::Vector2 & i_InitialPosition) :
	name_(_strdup(name ? name : "Unnamed")),
	position_(i_InitialPosition)

{
#ifdef _DEBUG_ACTOR_CONSTRUCTORS
	DEBUG_PRINT("Creating actor named %s using standard constructor.", pName ? pName : "Unnamed" );
#endif // _DEBUG_ACTOR_CONSTRUCTORS
}

Actor::Actor(const Actor & other) :
	name_(other.name_ ? _strdup(other.name_) : nullptr),
	position_(other.position_)
{
#ifdef _DEBUG_ACTOR_CONSTRUCTORS
	DEBUG_PRINT("Creating actor named %s using copy constructor.", pName ? pName : "Unnamed");
#endif // _DEBUG_ACTOR_CONSTRUCTORS
}

Actor::~Actor()
{
	if (name_)
		free(name_);
}

Actor & Actor::operator=(const Actor & other)
{
#ifdef _DEBUG_ACTOR_CONSTRUCTORS
	DEBUG_PRINT("Reassigning actor named %s to %s using assignment operator.", pName ? pName : "Unnamed", i_Other.pName ? i_Other.pName : "Unnamed");
#endif // _DEBUG_ACTOR_CONSTRUCTORS

	if (name_)
		free(name_);
	
	name_ = other.name_ ? _strdup(other.name_) : nullptr;
	position_ = other.position_;

	return *this;
}

void Actor::Move(const Engine::Math::Vector2 & movement)
{
	position_ += movement;
}

void Actor::Output() const
{
	assert(name_);
	printf("%s is at [%4d,%4d]\n", name_, position_.x(), position_.y());
}

void Actor::SetSprite(GLib::Sprite* sprite)
{
	sprite_ = sprite;
}

const GLib::Sprite* Actor::GetSprite()
{
	return sprite_;
}


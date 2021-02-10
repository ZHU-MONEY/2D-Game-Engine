#pragma once
#ifndef ACTOR_
#define ACTOR_
#include "Engine/Math/Vector2.h"
#include "Glib\GLib.h"

class Actor
{
public:
	Actor(const char * name, const Engine::Math::Vector2 & initialPosition);

	~Actor();

	Actor(const Actor & other);
	Actor & operator=(const Actor & other);

	const char * Name() const { return name_; }
	void Move(const Engine::Math::Vector2 & movement);
	void Output() const;
	void SetSprite(GLib::Sprite* sprite);
	const GLib::Sprite* GetSprite();

private:
	char *							name_;
	Engine::Math::Vector2			position_;
	GLib::Sprite*					sprite_;
};
#endif


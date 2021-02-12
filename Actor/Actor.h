#pragma once
#ifndef ACTOR_
#define ACTOR_
#include "Engine/Math/Vector2.h"
#include "Glib\GLib.h"
#include "Engine/GameObject/GameObject.h"
using namespace Engine::Math;

class Actor
{
public:
	Actor(const char * name, const Vector2 & initialPosition);
	~Actor();

	Actor(const Actor & other);
	Actor & operator=(const Actor & other);

	const char * Name() const { return name_; }
	void Move(const Vector2 & movement);
	void Print() const;
	void Render();
	//void SetSprite(GLib::Sprite* sprite);
	//const GLib::Sprite* GetSprite();

private:
	char *							name_;
	Vector2							position_;
	GLib::Sprite*					sprite_;
};
#endif


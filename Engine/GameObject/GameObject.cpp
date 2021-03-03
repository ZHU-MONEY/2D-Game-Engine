#include "GameObject.h"
#include <Engine\EngineUtils.h>

StrongPtr<GameObject> GameObject::Create()
{
	return StrongPtr<GameObject>(new GameObject());
}

GameObject::GameObject() :
	position_(Vector2::ZERO),
	sprite_(EngineUtils::CreateSprite("data\\GoodGuy.dds"))
{
}

GameObject::~GameObject()
{
}


GameObject::GameObject(const GameObject& other)
{
	position_ = other.position_;
}


GameObject& GameObject::operator=(const GameObject& other)
{
	position_ = other.GetPosition();
	return *this;
}



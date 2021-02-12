#include "GameObject.h"

GameObject::GameObject() : position_()
{
}

GameObject::GameObject(const GameObject& other)
{
	position_ = other.GetPosition();
}


GameObject& GameObject::operator=(const GameObject& other)
{
	position_ = other.GetPosition();
	return *this;
}

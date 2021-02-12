#include "GameObject.h"
#include <Engine\EngineUtils.h>

GameObject::GameObject() :
	position_(Vector2::ZERO),
	sprite_(EngineUtils::CreateSprite("data\\GoodGuy.dds"))
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

void GameObject::Move(const Vector2& movement)
{

}

void GameObject::Render()
{
	if (sprite_)
	{
		static GLib::Point2D Offset = { -180.0f, -100.0f };
		GLib::Point2D Offset2 = { -180.0f, -100.0f };
		Offset2.x = position_.x();
		Offset2.y = position_.y();

		GLib::Render(*sprite_, Offset2, 0.0f, 0.0f);
	}
}

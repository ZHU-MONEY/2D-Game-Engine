#include "RenderableObject.h"

RenderableObject::RenderableObject()
{
}

RenderableObject::RenderableObject(Sprite* sprite) :
	objectPtr_(nullptr),
	sprite_(sprite)
{
	position_ = { 0.0f, 0.0f };
}

RenderableObject::RenderableObject(WeakPtr<GameObject>& gameObject, Sprite* sprite) :
	objectPtr_(gameObject),
	sprite_(sprite)
{
	position_ = { 0.0f, 0.0f };
}

RenderableObject::~RenderableObject()
{
	if (sprite_) {
		Release(sprite_);
		sprite_ = nullptr;
	}
}

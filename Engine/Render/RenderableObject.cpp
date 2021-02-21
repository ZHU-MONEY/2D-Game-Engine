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

void RenderableObject::Render()
{
	if (objectPtr_) {
		StrongPtr<GameObject> objectPtr_(objectPtr_);
		position_ = { objectPtr_->GetPosition().x(), objectPtr_->GetPosition().y()};
	}

	GLib::Render(*sprite_, position_, 0.0f, 0.0f);
}



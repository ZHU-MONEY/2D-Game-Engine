#include "RenderableObject.h"
#include "Renderer.h"

RenderableObject::RenderableObject() :

	objectPtr_(nullptr),
	sprite_(nullptr)
{
	position_ = { 0.0f, 0.0f };
	Renderer* rendererInstance = Renderer::GetInstance();
	rendererInstance->AddRenderableObject(this);
}



RenderableObject::RenderableObject(WeakPtr<GameObject>& gameObject) :
	objectPtr_(gameObject),
	sprite_(nullptr)
{
	position_ = { 0.0f, 0.0f };
	Renderer* rendererInstance = Renderer::GetInstance();
	rendererInstance->AddRenderableObject(this);
}

RenderableObject::RenderableObject(Sprite* sprite) :
	objectPtr_(nullptr),
	sprite_(sprite)
{
	position_ = { 0.0f, 0.0f };
	Renderer* rendererInstance = Renderer::GetInstance();
	rendererInstance->AddRenderableObject(this);
}

RenderableObject::RenderableObject(WeakPtr<GameObject>& gameObject, Sprite* sprite) :
	objectPtr_(gameObject),
	sprite_(sprite)
{
	position_ = { 0.0f, 0.0f };
	Renderer* rendererInstance = Renderer::GetInstance();
	rendererInstance->AddRenderableObject(this);
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
	if (this->objectPtr_) {
		StrongPtr<GameObject> objectPtr_(this->objectPtr_);
		position_ = { objectPtr_->GetPosition().x(), objectPtr_->GetPosition().y() };
	}

	GLib::Render(*sprite_, position_, 0.0f, 0.0f);
}



#include "RenderableObject.h"
#include "Renderer.h"

RenderableObject::RenderableObject() :

	objectPtr_(nullptr),
	sprite_(EngineUtils::CreateSprite("data\\default sprite.dds")),
	rotation_(0.0f)
{
	position_ = { 0.0f, 0.0f };
	Renderer* rendererInstance = Renderer::GetInstance();
	rendererInstance->AddRenderableObject(this);
}



RenderableObject::RenderableObject(WeakPtr<GameObject>& gameObject) :
	objectPtr_(gameObject),
	sprite_(EngineUtils::CreateSprite("data\\default sprite.dds")),
	rotation_(0.0f)
{
	position_ = { 0.0f, 0.0f };
	//Renderer* rendererInstance = Renderer::GetInstance();
	//rendererInstance->AddRenderableObject(this);
}

RenderableObject::RenderableObject(Sprite* sprite) :
	objectPtr_(nullptr),
	sprite_(sprite),
	rotation_(0.0f)
{
	position_ = { 0.0f, 0.0f };
	//Renderer* rendererInstance = Renderer::GetInstance();
	//rendererInstance->AddRenderableObject(this);
}

RenderableObject::RenderableObject(WeakPtr<GameObject>& gameObject, Sprite* sprite) :
	objectPtr_(gameObject),
	sprite_(sprite),
	rotation_(0.0f)
{
	position_ = { 0.0f, 0.0f };
	//Renderer* rendererInstance = Renderer::GetInstance();
	//rendererInstance->AddRenderableObject(this);
}

RenderableObject::~RenderableObject()
{

	if (sprite_) {
		Release(sprite_);
		sprite_ = nullptr;
	}
}

StrongPtr<RenderableObject> RenderableObject::CreateROStrongPtr(RenderableObject* ro)
{
	StrongPtr<RenderableObject> ROStrongPtr = StrongPtr<RenderableObject>(ro);
	Renderer* rendererInstance = Renderer::GetInstance();
	rendererInstance->AddRenderableObject(ROStrongPtr);


	return ROStrongPtr;
}


void RenderableObject::Render()
{
	if (this->objectPtr_) {
		StrongPtr<GameObject> objectPtr_(this->objectPtr_);
		position_ = { objectPtr_->GetPosition().x(), objectPtr_->GetPosition().y()};
		rotation_ = objectPtr_->GetRotation();
	}

	GLib::Render(*sprite_, position_, 0.0f, rotation_);
	
}



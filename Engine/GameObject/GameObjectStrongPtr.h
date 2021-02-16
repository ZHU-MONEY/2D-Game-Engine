#pragma once
#include "Engine/GameObject/ReferenceCounter.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/GameObject/GameObjectWeakPtr.h"

class GameObjectStrongPtr
{
public:

	inline GameObjectStrongPtr() :
		gameObject_(nullptr),
		referenceCounter_(nullptr)
	{}

	inline GameObjectStrongPtr(GameObject* go) :
		gameObject_(go),
		referenceCounter_(go ? new ReferenceCounter(1, 0) : nullptr)
	{}
	inline ~GameObjectStrongPtr()
	{
		if (referenceCounter_)
		{
			if (--(referenceCounter_->strongPtrCount) <= 0)
			{
				if (gameObject_)
				{
					delete gameObject_;
					gameObject_ = nullptr;
				}

				if (referenceCounter_->weakPtrCount <= 0)
				{
					if (referenceCounter_)
					{
						delete referenceCounter_;
						referenceCounter_ = nullptr;
					}
				}
			}
		}
		return;
	}

	inline GameObjectStrongPtr(const GameObjectStrongPtr& copy) :
		gameObject_(copy.gameObject_),
		referenceCounter_(copy.referenceCounter_)
	{
		referenceCounter_->strongPtrCount++;
	}

	inline GameObjectStrongPtr(GameObjectStrongPtr&& copy) :
		gameObject_(copy.gameObject_),
		referenceCounter_(copy.referenceCounter_)
	{
		copy.gameObject_ = nullptr;
		copy.referenceCounter_ = nullptr;
	}

	//create fron weak pointer
	inline GameObjectStrongPtr(const GameObjectWeakPtr& otherWeakPointer) :
		gameObject_(otherWeakPointer.GetGameObject()),
		referenceCounter_(otherWeakPointer.GetReferenceCounter())
	{
		referenceCounter_->strongPtrCount++;
	}

	inline GameObject* operator->() const { return gameObject_; };
	inline GameObject& operator*() const { return *gameObject_; };

	inline operator bool() const { return gameObject_ != nullptr; };

	inline GameObject* GetGameObject() const { return gameObject_; };
	inline ReferenceCounter* GetReferenceCounter() const { return referenceCounter_; };

private:
	GameObject* gameObject_;
	ReferenceCounter* referenceCounter_;
};

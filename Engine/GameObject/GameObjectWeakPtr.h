#pragma once
#include "Engine/GameObject/GameObject.h"
#include "Engine/GameObject/ReferenceCounter.h"
#include "Engine/GameObject/GameObjectStrongPtr.h"

class GameObjectWeakPtr
{
public:
	//is default constructor really needed for this one?
	inline GameObjectWeakPtr() :
		gameObject_(nullptr),
		referenceCounter_(nullptr)
	{}
	// create from strong pointer
	inline GameObjectWeakPtr(const GameObjectStrongPtr& otherStrongPointer) :
		gameObject_(otherStrongPointer.GetGameObject()),
		referenceCounter_(otherStrongPointer.GetReferenceCounter())
	{
		referenceCounter_->weakPtrCount++;
	}
	inline ~GameObjectWeakPtr()
	{
		if (referenceCounter_)
		{
			if (--(referenceCounter_->weakPtrCount) <= 0 && referenceCounter_->strongPtrCount <= 0)
			{
				if (referenceCounter_)
				{
					delete referenceCounter_;
					referenceCounter_ = nullptr;
				}
			}
		}
		return;
	}

	inline GameObjectWeakPtr(const GameObjectWeakPtr& copy) :
		gameObject_(copy.gameObject_),
		referenceCounter_(copy.referenceCounter_)
	{
		referenceCounter_->weakPtrCount++;
	}

	inline GameObjectWeakPtr(GameObjectWeakPtr&& copy) :
		gameObject_(copy.gameObject_),
		referenceCounter_(copy.referenceCounter_)
	{
		copy.gameObject_ = nullptr;
		copy.referenceCounter_ = nullptr;
	}



	inline operator bool() const { return gameObject_ != nullptr; };

	inline GameObject* GetGameObject() const { return gameObject_; };
	inline ReferenceCounter* GetReferenceCounter() const { return referenceCounter_; };


private:
	GameObject* gameObject_;
	ReferenceCounter* referenceCounter_;
};
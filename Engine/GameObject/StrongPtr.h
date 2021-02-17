#pragma once
#include "Engine/GameObject/ReferenceCounter.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/GameObject/WeakPtr.h"
template<class T>
class StrongPtr
{
public:

	inline StrongPtr() :
		objectPtr_(nullptr),
		referenceCounter_(nullptr)
	{}

	inline StrongPtr(GameObject* go) :
		objectPtr_(go),
		referenceCounter_(go ? new ReferenceCounter(1, 0) : nullptr)
	{}
	inline ~StrongPtr()
	{
		if (referenceCounter_)
		{
			if (--(referenceCounter_->strongPtrCount) <= 0)
			{
				if (objectPtr_)
				{
					delete objectPtr_;
					objectPtr_ = nullptr;
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

	inline StrongPtr(const StrongPtr& copy) :
		objectPtr_(copy.objectPtr_),
		referenceCounter_(copy.referenceCounter_)
	{
		referenceCounter_->strongPtrCount++;
	}

	inline StrongPtr(StrongPtr&& copy) :
		objectPtr_(copy.objectPtr_),
		referenceCounter_(copy.referenceCounter_)
	{
		copy.objectPtr_ = nullptr;
		copy.referenceCounter_ = nullptr;
	}

	//create fron weak pointer
	inline StrongPtr(const WeakPtr<T>& otherWeakPointer) :
		objectPtr_(otherWeakPointer.GetObjectPtr()),
		referenceCounter_(otherWeakPointer.GetReferenceCounter())
		//objectPtr_(otherWeakPointer.objectPtr_),
		//referenceCounter_(otherWeakPointer.referenceCounter_)
	{
		referenceCounter_->strongPtrCount++;
	}

	inline T* operator->() const { return objectPtr_; };
	inline T& operator*() const { return *objectPtr_; };

	inline bool operator==(const StrongPtr& other) const { return objectPtr_ == other.objectPtr_ };
	inline bool operator!=(const StrongPtr& other) const { return objectPtr_ != other.objectPtr_ };
	inline operator bool() const { return objectPtr_ != nullptr; };

	inline T* GetObjectPtr() const { return objectPtr_; };
	inline ReferenceCounter* GetReferenceCounter() const { return referenceCounter_; };

private:
	T* objectPtr_;
	ReferenceCounter* referenceCounter_;
};

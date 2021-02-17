#pragma once
#include "Engine/GameObject/GameObject.h"
#include "Engine/GameObject/ReferenceCounter.h"
#include "Engine/GameObject/StrongPtr.h"
template<class T>
class WeakPtr
{
public:
	//is default constructor really needed for this one?
	inline WeakPtr() :
		objectPtr_(nullptr),
		referenceCounter_(nullptr)
	{}
	// create from strong pointer
	inline WeakPtr(const StrongPtr& otherStrongPointer) :
		objectPtr_(otherStrongPointer.GetGameObject()),
		referenceCounter_(otherStrongPointer.GetReferenceCounter())
	{
		referenceCounter_->weakPtrCount++;
	}
	inline ~WeakPtr()
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

	inline WeakPtr(const WeakPtr& copy) :
		objectPtr_(copy.objectPtr_),
		referenceCounter_(copy.referenceCounter_)
	{
		referenceCounter_->weakPtrCount++;
	}

	inline WeakPtr(WeakPtr&& copy) :
		objectPtr_(copy.objectPtr_),
		referenceCounter_(copy.referenceCounter_)
	{
		copy.objectPtr_ = nullptr;
		copy.referenceCounter_ = nullptr;
	}


	inline bool operator==(const WeakPtr& other) const { return objectPtr_ == other.objectPtr_ };
	inline bool operator!=(const WeakPtr& other) const { return objectPtr_ != other.objectPtr_ };
	inline operator bool() const { return objectPtr_ != nullptr; };

	inline T* GetObjectPtr() const { return objectPtr_; };
	inline ReferenceCounter* GetReferenceCounter() const { return referenceCounter_; };


private:
	T* objectPtr_;
	ReferenceCounter* referenceCounter_;
};
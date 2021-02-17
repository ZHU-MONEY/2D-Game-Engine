#pragma once
//#include "Engine/GameObject/ReferenceCounter.h"
//#include "Engine/GameObject/StrongPtr.h"

template<class T>
class StrongPtr;

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
	inline WeakPtr(const StrongPtr<T>& otherStrongPointer) :
		objectPtr_(otherStrongPointer.GetObjectPtr()),
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

	inline WeakPtr& operator=(const WeakPtr& copy) {
		// check for self assignment
		if (this != &copy)
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

			objectPtr_ = copy.objectPtr_;
			referenceCounter_ = copy.referenceCounter_;

			if (referenceCounter_)
			{
				referenceCounter_->weakPtrCount++;
			}
		}
		return *this;
	};


	inline bool operator==(const WeakPtr& other) const { return objectPtr_ == other.objectPtr_ };
	inline bool operator!=(const WeakPtr& other) const { return objectPtr_ != other.objectPtr_ };
	inline operator bool() const { return objectPtr_ != nullptr; };

	inline T* GetObjectPtr() const { return objectPtr_; };
	inline ReferenceCounter* GetReferenceCounter() const { return referenceCounter_; };


private:
	T* objectPtr_;
	ReferenceCounter* referenceCounter_;
};

#pragma once
struct ReferenceCounter
{
public:
	ReferenceCounter(long strongPtrAmount, long weakPtrAmount) :
		strongPtrCount(strongPtrAmount),
		weakPtrCount(weakPtrAmount)
	{}
	long strongPtrCount;
	long weakPtrCount;
};
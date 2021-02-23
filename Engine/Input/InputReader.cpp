#include "InputReader.h"

InputReader* InputReader::instance_ = nullptr;

InputReader* InputReader::Create()
{
	if (!instance_)
	{
		instance_ = new InputReader();
	}
	return instance_;
}

void InputReader::Destroy()
{
	if (instance_)
	{
		delete instance_;
		instance_ = nullptr;
	}
}

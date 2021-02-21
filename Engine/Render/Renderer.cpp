#include "Renderer.h"

Renderer* Renderer::Create()
{
	if (!instance_)
	{
		instance_ = new Renderer();
	}
	return instance_;
}

void Renderer::Destroy()
{
	if (instance_)
	{
		delete instance_;
		instance_ = nullptr;
	}
}

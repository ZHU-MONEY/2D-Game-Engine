#include "Renderer.h"

//static member initialize
Renderer* Renderer::instance_ = nullptr;



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

void Renderer::Run()
{
	// Tell GLib that we want to start rendering
	GLib::BeginRendering(DirectX::Colors::Black);
	// Tell GLib that we want to render some sprites
	GLib::Sprites::BeginRendering();

	for each (StrongPtr<RenderableObject>  ro in renderableObjects_)
	{
		if (ro.GetObjectPtr()->GetObjectPtr().GetObjectPtr()->GetIsActive())
		ro->Render();
	}

	// Tell GLib we're done rendering sprites
	GLib::Sprites::EndRendering();
	// Tell GLib we're done rendering
	GLib::EndRendering();
}

void Renderer::AddRenderableObject(StrongPtr<RenderableObject> ro)
{
	if (std::find(renderableObjects_.begin(), renderableObjects_.end(), ro) != renderableObjects_.end())
	{
		//ro is already in vector
		return;
	}
	else {
		renderableObjects_.push_back(ro);
	}
}

void Renderer::RemoveRenderableObject(StrongPtr<RenderableObject> ro)
{
	auto it = std::find(renderableObjects_.begin(), renderableObjects_.end(), ro);
	if (it == renderableObjects_.end())
	{
		//po is NOT in vector
		return;
	}
	else {
		renderableObjects_.erase(it);
	}
}

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	renderableObjects_.clear();

}

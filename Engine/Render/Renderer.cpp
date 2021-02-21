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

void Renderer::Run()
{
	// Tell GLib that we want to start rendering
	GLib::BeginRendering(DirectX::Colors::Blue);
	// Tell GLib that we want to render some sprites
	GLib::Sprites::BeginRendering();

	for each (RenderableObject * ro in renderableObjects_)
	{
		ro->Render();
	}

	// Tell GLib we're done rendering sprites
	GLib::Sprites::EndRendering();
	// Tell GLib we're done rendering
	GLib::EndRendering();
}

void Renderer::AddRenderableObject(RenderableObject* ro)
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

void Renderer::RemoveRenderableObject(RenderableObject* ro)
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

Renderer::~Renderer()
{
	renderableObjects_.clear();
}

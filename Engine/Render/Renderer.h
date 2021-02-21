#pragma once
#include "Engine/Render/RenderableObject.h"
#include <DirectXColors.h>
#include <vector>
class Renderer
{
public:

	static Renderer* Create();
	inline static Renderer* GetInstance() { return instance_; };
	static void Destroy();
	void Run();

	void AddRenderableObject(RenderableObject* ro);
	void RemoveRenderableObject(RenderableObject* ro);

private:

	std::vector<RenderableObject*> renderableObjects_;
	static Renderer* instance_;
	Renderer();
	~Renderer();
};


#pragma once
#include "Engine/Render/RenderableObject.h"
class Renderer
{
public:

	static Renderer* Create();
	inline static Renderer* GetInstance() { return instance_; };
	static void Destroy();
	void Run(float dt);

private:
	static Renderer* instance_;
	Renderer();
	~Renderer();
};


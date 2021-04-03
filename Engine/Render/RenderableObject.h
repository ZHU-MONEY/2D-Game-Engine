#pragma once
#include "GLib/GLib.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/GameObject/WeakPtr.h"
#include "Engine/GameObject/StrongPtr.h"
#include <Engine\EngineUtils.h>

using namespace GLib;
class RenderableObject
{
public:

	//default constructor
	RenderableObject();
	//constructor
	RenderableObject(WeakPtr<GameObject>& gameObject);
	RenderableObject(Sprite* sprite);
	RenderableObject(WeakPtr<GameObject>& gameObject, Sprite* sprite);
	//destructor
	~RenderableObject();

	StrongPtr<RenderableObject> CreateROStrongPtr(RenderableObject* ro);

	//testing
	inline void SetSprite(Sprite* s) { sprite_ = s; };

	void Render();


private:
	WeakPtr<GameObject> objectPtr_;
	Sprite* sprite_;
	Point2D position_;
	float rotation_;
};


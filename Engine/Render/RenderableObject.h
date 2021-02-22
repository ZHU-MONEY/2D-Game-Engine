#pragma once
#include "GLib/GLib.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/GameObject/WeakPtr.h"
#include "Engine/GameObject/StrongPtr.h"

using namespace GLib;
class RenderableObject
{
public:
	//default constructor
	RenderableObject();

	//constructor
	RenderableObject(Sprite* sprite);
	RenderableObject(WeakPtr<GameObject>& gameObject, Sprite* sprite);

	//destructor
	~RenderableObject();
private:
	WeakPtr<GameObject> objectPtr_;
	Sprite* sprite_;
	Point2D position_;
};


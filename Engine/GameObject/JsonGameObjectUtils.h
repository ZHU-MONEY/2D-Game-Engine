#pragma once
#include "Engine/json.hpp"

#include "Engine/Physics/PhysicsObject.h"
#include "Engine/Render/RenderableObject.h"

#include "Engine/EngineUtils.h"

#include "Engine/GameObject/WeakPtr.h"
#include "Engine/GameObject/StrongPtr.h"
#include "Engine/GameObject/GameObject.h"
using json = nlohmann::json;
class JsonGameObjectUtils
{
public:
	static StrongPtr<GameObject> CreateGameObjectFromJson(const char* filePath);
private:

};

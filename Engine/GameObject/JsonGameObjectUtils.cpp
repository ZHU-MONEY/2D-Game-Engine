#pragma warning(disable : 4996)
#include "JsonGameObjectUtils.h"

#include <iostream>

StrongPtr<GameObject> JsonGameObjectUtils::CreateGameObjectFromJson(const char* filePath)
{
	FILE* file = fopen(filePath, "r");

	if (file == nullptr) {
		std::cout << "file not found";
	}

	//json jsonObject = json::parse("xxx.json",nullptr,false);

	json jsonObject = json::parse(file, nullptr, false);

	//this if needs to be paired with parse above
	//check if parse failed
	if (jsonObject.is_discarded())
	{
		// parse failed
	}
	else {
		StrongPtr<GameObject> go = GameObject::Create();

		if (jsonObject.contains("name"))
		{
			//set name
		}

		if (jsonObject.contains("position"))
		{
			json pos = jsonObject["position"];

			assert(pos.is_array());
			assert(pos.size() == 2);
			assert(pos[0].is_number() && pos[1].is_number());

			go->SetPosition(Vector2(pos[0], pos[1]));
		}

		if (jsonObject.contains("physics"))
		{
			//create a phisics object
			PhysicsObject* po = new PhysicsObject(WeakPtr<GameObject>(go));

			json jsonPhysicsObject = jsonObject["physics"];
			if (jsonPhysicsObject.contains("mass"))
			{
				po->SetMass(jsonPhysicsObject["mass"]);
			}

			if (jsonPhysicsObject.contains("coefficient drag"))
			{
				po->SetCoefficientDrag(jsonPhysicsObject["coefficient drag"]);
			}

		}

		if (jsonObject.contains("render"))
		{
			//create a renderable object
			RenderableObject* ro = new RenderableObject(WeakPtr<GameObject>(go));

			json jsonRenderableObject = jsonObject["render"];
			if (jsonRenderableObject.contains("sprite"))
			{
				ro->SetSprite(EngineUtils::CreateSprite(jsonRenderableObject["sprite"].get<std::string>().c_str()));
			}
		}

		if (jsonObject.contains("collider"))
		{

		}

		return go;
	}
	
	return nullptr;
}

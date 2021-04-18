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

		if (jsonObject.contains("rotation"))
		{
			//json rot = jsonObject["rotation"];

			go->SetRotation(jsonObject["rotation"]);
		}

		//this will determine how big is the AABB
		if (jsonObject.contains("size"))
		{
			json size = jsonObject["size"];

			go->SetAABB({ Vector2::ZERO, Vector2(size[0]/2.0f, size[1]/2.0f)});
		}

		if (jsonObject.contains("static"))
		{
			go->SetIsStatic(jsonObject["static"]);
		}

		if (jsonObject.contains("physics"))
		{
			//create a phisics object
			PhysicsObject* po = new PhysicsObject(WeakPtr<GameObject>(go));
			StrongPtr<PhysicsObject> pos = po->CreatePOStrongPtr(po);
			json jsonPhysicsObject = jsonObject["physics"];

			if (jsonPhysicsObject.contains("collideable"))
			{
				pos->SetCollideable(jsonPhysicsObject["collideable"]);
				ColliderSystem* colliderSystemInstance = ColliderSystem::GetInstance();
				colliderSystemInstance->AddPhysicsObject(WeakPtr<PhysicsObject>(pos));

			}

			if (jsonPhysicsObject.contains("controllable"))
			{
				pos->SetControllable(jsonPhysicsObject["controllable"]);
			}
			if (jsonPhysicsObject.contains("mass"))
			{
				pos->SetMass(jsonPhysicsObject["mass"]);
			}

			if (jsonPhysicsObject.contains("coefficient drag"))
			{
				pos->SetCoefficientDrag(jsonPhysicsObject["coefficient drag"]);
			}
		}

		if (jsonObject.contains("render"))
		{
			//create a renderable object
			RenderableObject* ro = new RenderableObject(WeakPtr<GameObject>(go));
			StrongPtr<RenderableObject> ros = ro->CreateROStrongPtr(ro);
			//ro->CreateROStrongPtr(ro);
			json jsonRenderableObject = jsonObject["render"];
			if (jsonRenderableObject.contains("sprite"))
			{
				//this is a very, very weird way of doing this, it removes the default sprite
				ro->~RenderableObject();

				Sprite* sprite(EngineUtils::CreateSprite(jsonRenderableObject["sprite"].get<std::string>().c_str()));
				ros->SetSprite(sprite);
				
			}

		}

		if (jsonObject.contains("collider"))
		{

		}

		return go;
	}
	
	return nullptr;
}

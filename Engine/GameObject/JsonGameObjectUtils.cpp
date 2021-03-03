#include "JsonGameObjectUtils.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/Physics/PhysicsObject.h"
#include "Engine/Render/RenderableObject.h"
#include "Engine/EngineUtils.h"

void JsonGameObjectUtils::CreateGameObjectFromJson(const char* filePath)
{
	FILE* file = fopen(filePath, "r");

	json jsonObject = json::parse("xxx.json",nullptr,false);

	//json jsonObject = json::parse<FILE*>(file, nullptr, false);


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

			if (jsonObject.contains("mass"))
			{
				po->SetMass(jsonObject["mass"]);
			}

			if (jsonObject.contains("coefficient drag"))
			{
				po->SetCoefficientDrag(jsonObject["coefficient drag"]);
			}

			//add po to the physics system?????    How do I get a reference of physiscs syentem in here??
		}

		if (jsonObject.contains("render"))
		{
			//create a renderable object
			RenderableObject* ro = new RenderableObject(WeakPtr<GameObject>(go));

			if (jsonObject.contains("sprite"))
			{
				//const char* spriteFilePath = jsonObject["sprite"].get<std::string>().c_str();
				//ro->SetSprite(EngineUtils::CreateSprite(spriteFilePath));

				ro->SetSprite(EngineUtils::CreateSprite(jsonObject["sprite"].get<std::string>().c_str()));
			}
		}

		if (jsonObject.contains("collider"))
		{

		}
	}
	
}

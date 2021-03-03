#pragma once
#include "Engine/json.hpp"
using json = nlohmann::json;
class JsonGameObjectUtils
{
public:
	static void CreateGameObjectFromJson(const char* filePath);
private:

};

#ifndef GAME_OBJECT_
#define GAME_OBJECT_
#include "Engine/Math/Vector2.h"
using namespace Engine::Math;
class GameObject
{
public:
	GameObject();
	~GameObject();

	GameObject(const GameObject& other);
	GameObject& operator=(const GameObject& other);

	inline void SetPosition(const Vector2& position) { position_ = position; };
	inline Vector2 GetPosition() const { return position_; };

protected:
	Vector2 position_;
};


#endif // !GAME_OBJECT_



#pragma once
#include "Engine/Math/Vector2.h"
#include "GLib/GLib.h"
#include "Engine/GameObject/StrongPtr.h"
class GameObject
{
public:
	static StrongPtr<GameObject> Create();
	GameObject();
	~GameObject();


	GameObject(const GameObject& other);
	GameObject& operator=(const GameObject& other);

	inline void SetPosition(const Vector2& position) { position_ = position; };
	inline Vector2 GetPosition() const { return position_; };

	void Move(const Vector2& movement);

	void Render();

protected:
	GLib::Sprite* sprite_;
	Vector2 position_;
};





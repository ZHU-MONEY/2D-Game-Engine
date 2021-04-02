#pragma once
#include "Engine/Math/Vector2.h"
#include "GLib/GLib.h"
#include "Engine/GameObject/StrongPtr.h"
#include <vector>
#include "Engine/Syncronization/ScopeLock.h"
#include "Engine/Syncronization/Mutex.h"
#include "Engine/Math/AABB.h"
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

	inline void SetRotation(const float& rotation) { rotation_ = rotation; };
	inline float GetRotation() const { return rotation_; };

	inline void SetAABB(const AABB& aabb) { aabb_ = aabb; };
	inline AABB GetAABB() const { return aabb_; };
	
	// This will move GameObjects from NewGameObjects -> AllGameObjects
	static void CheckForNewGameObjects();

	// This adds a new GameObject to NewGameObjects
	static void AddNewGameObject(StrongPtr<GameObject> i_pNewGameObject);

	// This is the mutex we use to guard against accessing NewGameObjects simultaneously on multiple threads
	//static Engine::Mutex NewGameObjectMutex;

protected:
	Vector2 position_;
	float rotation_;
	AABB aabb_;

private:
	// this is our master list of GameObjects
	//static std::vector<StrongPtr<GameObject>> AllGameObjects;

	//static std::vector<StrongPtr<GameObject>> NewGameObjects;
};





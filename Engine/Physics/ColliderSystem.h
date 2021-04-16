#pragma once

#include <mutex>
#include <vector>
#include <algorithm>

#include "Engine/Math/Matrix4x4.h"
#include "Engine/Math/MathUtils.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/Physics/PhysicsObject.h"

// forward declarations
struct AABB;
class Matrix4x4;
class PhysicsObject;

struct CollisionPair
{
	float time;
	Vector2	normalA;
	Vector2	normalB;
	WeakPtr<PhysicsObject>	objectA;
	WeakPtr<PhysicsObject>	objectB;
};

class ColliderSystem
{
private:
	ColliderSystem();
	~ColliderSystem();

	static ColliderSystem* instance_;
	size_t collideableObjectsAmount_;
	//std::vector<PhysicsObject*> collideableObjects_;
	std::vector<WeakPtr<PhysicsObject>> collideableObjects_;
	std::mutex colliderMutex_;

	std::vector<CollisionPair>  collided_objects_;

public:
	static ColliderSystem* Create();
	static inline ColliderSystem* GetInstance() {return instance_;};
	static void Destroy();
	void Run(float dt);

	// add and remove physics objects
	void AddPhysicsObject(WeakPtr<PhysicsObject>& poWeakPtr);
	void RemovePhysicsObject(WeakPtr<PhysicsObject>& poWeakPtr);


};


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


class ColliderSystem
{
private:
	bool CheckSeparationForAxis(const float i_relative_vel_WtoA, const float i_a_aabb_center, const float i_a_aabb_extents, const float i_B_center_in_A, const float i_B_extents_in_a, const float i_dt, float& o_t_close, float& o_t_open);
	ColliderSystem();
	~ColliderSystem();

	static ColliderSystem* instance_;
	size_t num_physics_objects_;
	//std::vector<PhysicsObject*> collideableObjects_;
	std::vector<WeakPtr<PhysicsObject>> collideableObjects_;
	std::mutex colliderMutex_;

public:
	static ColliderSystem* Create();
	static inline ColliderSystem* GetInstance() {return instance_;};
	static void Destroy();
	void Run(float dt);

	// add and remove physics objects
	void AddPhysicsObject(WeakPtr<PhysicsObject>& poWeakPtr);
	void RemovePhysicsObject(WeakPtr<PhysicsObject>& poWeakPtr);



};


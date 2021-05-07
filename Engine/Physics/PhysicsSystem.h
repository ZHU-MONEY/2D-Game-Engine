#pragma once
#include <vector>
#include "PhysicsObject.h"

class PhysicsSystem
{
private:
	PhysicsSystem();
	~PhysicsSystem();

	static PhysicsSystem* instance_;
	std::vector<StrongPtr<PhysicsObject>> physicsObjects_;

public:
	static PhysicsSystem* Create();
	inline static PhysicsSystem* GetInstance() { return instance_; };
	inline std::vector<StrongPtr<PhysicsObject>> GetPhysicsObjects() { return physicsObjects_; };
	static void Destroy();
	void Run(float dt);

	void AddPhysicsObject(StrongPtr<PhysicsObject> po);
	void RemovePhysicsObject(StrongPtr<PhysicsObject> po);
};
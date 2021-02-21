#pragma once
#include <vector>
#include "PhysicsObject.h"
//#include<algorithm>

class PhysicsSystem
{
private:
	PhysicsSystem();
	~PhysicsSystem();

	static PhysicsSystem* instance_;
	std::vector<PhysicsObject*> physicsObjects_;

public:
	static PhysicsSystem* Create();
	inline static PhysicsSystem* GetInstance() { return instance_; };
	static void Destroy();
	void Run(float dt);

	void AddPhysicsObject(PhysicsObject* po);
	void RemovePhysicsObject(PhysicsObject* po);
};
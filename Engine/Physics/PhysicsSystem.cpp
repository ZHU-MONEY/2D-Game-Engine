#include "PhysicsSystem.h"

//static member init
PhysicsSystem* PhysicsSystem::instance_ = nullptr;

//constructor
PhysicsSystem::PhysicsSystem()
{
}

//destructor
PhysicsSystem::~PhysicsSystem()
{
}

PhysicsSystem* PhysicsSystem::Create()
{
	if (!instance_)
	{
		instance_ = new PhysicsSystem();
	}
	return instance_;
}

void PhysicsSystem::Destroy()
{
	if (instance_)
	{
		delete instance_;
		instance_ = nullptr;
	}
}

void PhysicsSystem::Run(float dt)
{
	for each (PhysicsObject * po in physicsObjects_)
	{
		po->Update(dt);
	}
}

void PhysicsSystem::AddPhysicsObject(PhysicsObject* po)
{
	if (std::find(physicsObjects_.begin(), physicsObjects_.end(), po) != physicsObjects_.end())
	{
		//po is already in vector
		return;
	}
	else {
		physicsObjects_.push_back(po);
	}
}

void PhysicsSystem::RemovePhysicsObject(PhysicsObject* po)
{
	auto it = std::find(physicsObjects_.begin(), physicsObjects_.end(), po);
	if (it == physicsObjects_.end())
	{
		//po is NOT in vector
		return;
	}
	else {
		physicsObjects_.erase(it);
	}
}

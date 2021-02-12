#include "PhysicsObject.h"

const float PhysicsObject::DEFAULT_MASS = 10.0f;
const float PhysicsObject::DEFAULT_COEFFICIENT_DRAG = 1.0f;

PhysicsObject::PhysicsObject() :
	gameObject_(nullptr),
	mass_(DEFAULT_MASS),
	coefficientDrag_(DEFAULT_COEFFICIENT_DRAG),
	currentVelocity_(Vector2::ZERO),
	currentForce_(Vector2::ZERO),
	currentAcceleration_(Vector2::ZERO)
{
}

PhysicsObject::PhysicsObject(GameObject* gameObject,float mass, float drag):
	gameObject_(gameObject),
	mass_(mass),
	coefficientDrag_(drag),
	currentVelocity_(Vector2::ZERO),
	currentForce_(Vector2::ZERO),
	currentAcceleration_(Vector2::ZERO)
{
}

PhysicsObject::~PhysicsObject()
{
	//Probably just need to remove pointer, if call delete on gameobject then the gameobject mightget deleted
	if (gameObject_) {
		//delete gameObject_;
		gameObject_ = nullptr;
	}
	
}

void PhysicsObject::Update(float dt)
{
	// save previous velocity and position
	Vector2 previousVelocity = currentVelocity_;
	Vector2 previousPosition = gameObject_->GetPosition();
	Vector2 previousForce = currentForce_;
	
	//midpoint method

	// calculate drag force, ------IMPORTANT: this force is NEGATIVE
	Vector2 dragForce = (currentVelocity_ * currentVelocity_) * (-coefficientDrag_);
	currentForce_ = previousForce + dragForce;
	Vector2 acceleration = currentForce_ * (1.0f/ mass_);
	currentVelocity_ = previousVelocity + (acceleration * dt);
	// Midpoint method, use *0.5 instead of /2
	Vector2 currentPosition = previousPosition + ((previousVelocity + currentVelocity_) * 0.5f) * dt;

	// update game object
	gameObject_->SetPosition(currentPosition);
}

void PhysicsObject::ApplyForce(const Vector2& inputForce)
{
	currentForce_ = currentForce_ + inputForce;
}

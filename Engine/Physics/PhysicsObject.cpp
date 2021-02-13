#include "PhysicsObject.h"

const float PhysicsObject::DEFAULT_MASS = 5.0f;
const float PhysicsObject::DEFAULT_COEFFICIENT_DRAG = 0.5f;
const float PhysicsObject::MAX_SPEED = 2.0f;
const float PhysicsObject::MIN_SPEED = 0.0001f;

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

	// calculate drag force
	Vector2 dragForce = (currentVelocity_ * currentVelocity_) * (coefficientDrag_);

	//black magic
	if ((currentVelocity_.x() < 0 && dragForce.x() > 0) || (currentVelocity_.x() > 0 && dragForce.x() < 0) ){
		dragForce.x(dragForce.x() * -1);
	}
	if ((currentVelocity_.y() < 0 && dragForce.y() > 0) || (currentVelocity_.y() > 0 && dragForce.y() < 0)) {
		dragForce.y(dragForce.y() * -1);
	}

	currentForce_ = previousForce - dragForce;
	Vector2 acceleration = currentForce_ * (1.0f/ mass_);
	currentVelocity_ = previousVelocity + (acceleration * dt);

	currentForce_ = Vector2::ZERO;



	//stop it, otherwise it will go to the other side
	//this is very very broken
	if (currentVelocity_.LengthSquared() < MIN_SPEED) {
		currentVelocity_ = Vector2::ZERO;
		previousVelocity = Vector2::ZERO;
	}

	//limit speed
	if (currentVelocity_.LengthSquared() > MAX_SPEED) {
		currentVelocity_ = previousVelocity;
	}


	// Midpoint method, use *0.5 instead of /2
	Vector2 currentPosition = previousPosition + (((previousVelocity + currentVelocity_) * 0.5f) * dt);

	// update game object
	gameObject_->SetPosition(currentPosition);
}

void PhysicsObject::ApplyForce(const Vector2& inputForce)
{
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];
	sprintf_s(Buffer, lenBuffer, "input force y %f\n", inputForce.y());
	OutputDebugStringA(Buffer);

	currentForce_ = currentForce_ + inputForce;
	//currentForce_.x(currentForce_.x() + inputForce.x());
	//currentForce_.y(currentForce_.y() + inputForce.y());
}

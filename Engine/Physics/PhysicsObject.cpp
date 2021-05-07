#include "PhysicsObject.h"
#include "Engine/Physics/PhysicsSystem.h"
#include "Engine/Physics/ColliderSystem.h"
#include "Engine/Input/InputReader.h"

const float PhysicsObject::DEFAULT_MASS = 1.0f;
const float PhysicsObject::DEFAULT_COEFFICIENT_DRAG = 0.1f;
const float PhysicsObject::MAX_SPEED = 1.0f;
const float PhysicsObject::MIN_SPEED = 0.0001f;

PhysicsObject::PhysicsObject() :
	objectPtr_(nullptr),
	controllable_(false),
	collideable_(false),
	mass_(DEFAULT_MASS),
	coefficientDrag_(DEFAULT_COEFFICIENT_DRAG),
	currentVelocity_(Vector2::ZERO),
	currentForce_(Vector2::ZERO),
	currentAcceleration_(Vector2::ZERO),
	isFinishedCollisionReaction_(false)
{
}

PhysicsObject::PhysicsObject(WeakPtr<GameObject>& gameObject) :
	objectPtr_(gameObject),
	controllable_(false),
	collideable_(false),
	mass_(DEFAULT_MASS),
	coefficientDrag_(DEFAULT_COEFFICIENT_DRAG),
	currentVelocity_(Vector2::ZERO),
	currentForce_(Vector2::ZERO),
	currentAcceleration_(Vector2::ZERO),
	isFinishedCollisionReaction_(false)
{
}

PhysicsObject::PhysicsObject(WeakPtr<GameObject>& gameObject,float mass, float drag):
	objectPtr_(gameObject),
	controllable_(false),
	collideable_(false),
	mass_(mass),
	coefficientDrag_(drag),
	currentVelocity_(Vector2::ZERO),
	currentForce_(Vector2::ZERO),
	currentAcceleration_(Vector2::ZERO),
	isFinishedCollisionReaction_(false)
{
}

PhysicsObject::~PhysicsObject()
{

}

StrongPtr<PhysicsObject> PhysicsObject::CreatePOStrongPtr(PhysicsObject* po)
{
	StrongPtr<PhysicsObject> POStrongPtr = StrongPtr<PhysicsObject>(po);
	PhysicsSystem* physicsSystemInstance = PhysicsSystem::GetInstance();
	physicsSystemInstance->AddPhysicsObject(POStrongPtr);




	return POStrongPtr;
}

void PhysicsObject::Update(float dt)
{
	StrongPtr<GameObject> objectPtr_(objectPtr_);

	// save previous velocity and position
	Vector2 previousVelocity = currentVelocity_;
	Vector2 previousPosition = objectPtr_->GetPosition();
	Vector2 previousForce = currentForce_;


	//midpoint method

	// calculate drag force
	Vector2 dragForce = (currentVelocity_ * currentVelocity_) * (coefficientDrag_);

	//make sure the drag is the opposite of velocity direction
	if ((currentVelocity_.x() < 0 && dragForce.x() > 0) || (currentVelocity_.x() > 0 && dragForce.x() < 0) ){
		dragForce.x(dragForce.x() * -1);
	}
	if ((currentVelocity_.y() < 0 && dragForce.y() > 0) || (currentVelocity_.y() > 0 && dragForce.y() < 0)) {
		dragForce.y(dragForce.y() * -1);
	}

	currentForce_ = previousForce - dragForce;

	float inverseMass = 1.0f / mass_;
	Vector2 acceleration = currentForce_ * (inverseMass);
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
	objectPtr_->SetPosition(currentPosition);

	isFinishedCollisionReaction_ = false;
}

void PhysicsObject::ApplyForce(const Vector2& inputForce)
{
	currentForce_.x(currentForce_.x() + inputForce.x());
	currentForce_.y(currentForce_.y() + inputForce.y());

}
float DotProduct(const Vector2& i_v1, const Vector2& i_v2)
{
	return (i_v1.x() * i_v2.x() + i_v1.y() * i_v2.y());
}

//this function is not being used in this game
void PhysicsObject::RespondToCollision(const Vector2& collisionNormal)
{
	//don't move it if static object
	if (this->objectPtr_.GetObjectPtr()->GetIsStatic()) {
		return;
	}
	if (isFinishedCollisionReaction_)
	{
		return;
	}

	if (currentVelocity_.IsZero()) {
		//currentVelocity_ = currentVelocity_ - collisionNormal;
	}
	else {
		currentVelocity_ = currentVelocity_ - (currentVelocity_ * Vector2(collisionNormal.x() + 0.01f, collisionNormal.y() + 0.01f) * 2);
		//currentVelocity_ = currentVelocity_ *0.1f;
	}

	isFinishedCollisionReaction_ = true;
}

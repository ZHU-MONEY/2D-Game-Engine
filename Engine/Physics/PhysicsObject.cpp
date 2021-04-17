#include "PhysicsObject.h"
#include "Engine/Physics/PhysicsSystem.h"
#include "Engine/Physics/ColliderSystem.h"
#include "Engine/Input/InputReader.h"

const float PhysicsObject::DEFAULT_MASS = 1.0f;
const float PhysicsObject::DEFAULT_COEFFICIENT_DRAG = 0.1f;
const float PhysicsObject::MAX_SPEED = 2.0f;
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
	//PhysicsSystem* physicsSystemInstance = PhysicsSystem::GetInstance();
	//physicsSystemInstance->AddPhysicsObject(this);
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
	//PhysicsSystem* physicsSystemInstance = PhysicsSystem::GetInstance();
	//physicsSystemInstance->AddPhysicsObject(this);
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
	//PhysicsSystem* physicsSystemInstance = PhysicsSystem::GetInstance();
	//physicsSystemInstance->AddPhysicsObject(this);
}

PhysicsObject::~PhysicsObject()
{
	objectPtr_;
}

StrongPtr<PhysicsObject> PhysicsObject::CreatePOStrongPtr(PhysicsObject* po)
{
	StrongPtr<PhysicsObject> POStrongPtr = StrongPtr<PhysicsObject>(po);
	PhysicsSystem* physicsSystemInstance = PhysicsSystem::GetInstance();
	physicsSystemInstance->AddPhysicsObject(POStrongPtr);

		//ColliderSystem* colliderSystemInstance = ColliderSystem::GetInstance();
		//colliderSystemInstance->AddPhysicsObject(WeakPtr<PhysicsObject>(POStrongPtr));



	return POStrongPtr;
}

void PhysicsObject::Update(float dt)
{

	//const size_t	lenBuffer = 65;
	//char			Buffer[lenBuffer];
	//sprintf_s(Buffer, lenBuffer, "strongPtr Counter BEFORE temporary creation: %d\n", GetGameObject().GetReferenceCounter()->strongPtrCount);
	//OutputDebugStringA(Buffer);

	StrongPtr<GameObject> objectPtr_(objectPtr_);


	//sprintf_s(Buffer, lenBuffer, "strongPtr Counter AFTER temporary creation:   %d\n", objectPtr_.GetReferenceCounter()->strongPtrCount);
	//OutputDebugStringA(Buffer);

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
	

	//currentForce_ += inputForce;
	currentForce_.x(currentForce_.x() + inputForce.x());
	currentForce_.y(currentForce_.y() + inputForce.y());

}
float DotProduct(const Vector2& i_v1, const Vector2& i_v2)
{
	return (i_v1.x() * i_v2.x() + i_v1.y() * i_v2.y());
}
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

	//InputReader* inputReaderInstance = InputReader::GetInstance();
	//if (!this->controllable_) {
	//	float pushSpeed = 0.2f;
	//	if (inputReaderInstance->isKey_W_Down) {
	//		this->ApplyForce(Vector2(0.0f, pushSpeed));
	//	}
	//	if (inputReaderInstance->isKey_D_Down) {
	//		this->ApplyForce(Vector2(pushSpeed, 0.0f));
	//	}
	//	if (inputReaderInstance->isKey_S_Down) {
	//		this->ApplyForce(Vector2(0.0f, -pushSpeed));
	//	}
	//	if (inputReaderInstance->isKey_A_Down) {
	//		this->ApplyForce(Vector2(-pushSpeed, 0.0f));
	//	}
	//}

	if (currentVelocity_.IsZero()) {
		//currentVelocity_ = currentVelocity_ - collisionNormal;
	}
	else {
		currentVelocity_ = currentVelocity_ - (currentVelocity_ * collisionNormal * 2);
		//currentVelocity_ = currentVelocity_ *0.1f;
	}

	isFinishedCollisionReaction_ = true;
}

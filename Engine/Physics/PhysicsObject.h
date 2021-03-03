#pragma once
#include "Engine/GameObject/GameObject.h"
#include "Engine/GameObject/WeakPtr.h"
#include "Engine/GameObject/StrongPtr.h"
class PhysicsObject
{
public:

	//default mass and drag coeffcient 
	static const float	DEFAULT_MASS;
	static const float	DEFAULT_COEFFICIENT_DRAG;
	static const float  MAX_SPEED;
	static const float  MIN_SPEED;
	PhysicsObject();
	PhysicsObject(WeakPtr<GameObject>& gameObject);
	PhysicsObject(WeakPtr<GameObject>& gameObject,float mass, float drag);
	~PhysicsObject();

	void Update(float dt);
	void ApplyForce(const Vector2& inputForce);

	// setter getter
	inline WeakPtr<GameObject> GetGameObject() const { return objectPtr_; };
	inline void SetGameObject(const WeakPtr<GameObject>& gameObject) { objectPtr_ = gameObject; };
	inline float GetMass() const { return mass_; };
	inline void SetMass(const float mass) { mass_ = mass; };
	inline float GetCoefficientDrag() const { return coefficientDrag_; };
	inline void SetCoefficientDrag(const float drag) { coefficientDrag_ = drag; };
	inline const Vector2 GetVelocity() const { return currentVelocity_; };
	inline void SetVelocity(const Vector2& velocity) { currentVelocity_ = velocity; };
	inline const Vector2 GetForce() const { return currentForce_; };
	inline void SetForce(const Vector2& force) { currentForce_ = force; };
	inline const Vector2 GetAcceleration() const { return currentAcceleration_; };
	inline void SetAcceleration(const Vector2& acceleration) { currentAcceleration_ = acceleration; };

private:

	WeakPtr<GameObject> objectPtr_;
	float mass_;
	float coefficientDrag_;
	Vector2 currentVelocity_;
	Vector2 currentForce_;
	Vector2 currentAcceleration_;


};


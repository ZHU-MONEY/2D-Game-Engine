#pragma once
#include "Engine/GameObject/GameObject.h"

using namespace Engine::Math;
class PhysicsObject
{
public:

	//default mass and drag coeffcient 
	static const float	DEFAULT_MASS;
	static const float	DEFAULT_COEFFICIENT_DRAG;
	PhysicsObject();
	PhysicsObject(GameObject* gameObject,float mass, float drag);
	~PhysicsObject();

	void Update(float dt);

	// setter getter
	inline GameObject* GetGameObject() const { return gameObject_; };
	inline void SetGameObject(GameObject* gameObject) { gameObject_ = gameObject; };
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

	GameObject* gameObject_;
	float mass_;
	float coefficientDrag_;
	Vector2 currentVelocity_;
	Vector2 currentForce_;
	Vector2 currentAcceleration_;


};


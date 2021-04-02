#include "Engine/Physics/ColliderSystem.h"
#include <cassert>


// static member initialization
ColliderSystem* ColliderSystem::instance_ = nullptr;

ColliderSystem::ColliderSystem() : num_physics_objects_(0)
{}

ColliderSystem::~ColliderSystem()
{
	collideableObjects_.clear();
	num_physics_objects_ = 0;
}

ColliderSystem* ColliderSystem::Create()
{
	if (!instance_)
	{
		instance_ = new ColliderSystem();
	}
	return instance_;
}

void ColliderSystem::Destroy()
{
	if (instance_)
	{
		delete instance_;
		instance_ = nullptr;
	}
}

void ColliderSystem::Run(float dt)
{
	for (size_t i = 0; i < num_physics_objects_; i++)
	{
		// get physics object A

		//StrongPtr<PhysicsObject> physicsObjectA = StrongPtr<PhysicsObject>(collideableObjects_[i]);
		PhysicsObject* physicsObjectA = collideableObjects_[i].GetObjectPtr();

		// get game object A
		const StrongPtr<GameObject> gameObjectA = physicsObjectA->GetGameObject().GetObjectPtr();
		// get A's AABB
		const AABB aAABB = gameObjectA->GetAABB();



		// calculate transform to convert from object A to world coordinates
		Matrix4x4 matARotation = Matrix4x4::GetRotationZ(gameObjectA.GetObjectPtr()->GetRotation());
		Matrix4x4 matATranslation = Matrix4x4::GetTranslation(gameObjectA.GetObjectPtr()->GetPosition());
		Matrix4x4 matAToWorld = matATranslation * matARotation;

		// calculate transform to convert world to object A coordinates
		Matrix4x4 matWorldToA(matAToWorld.GetInverse());

		for (size_t j = 0; j < num_physics_objects_; j++)
		{
			// don't compute collisions with self
			if (collideableObjects_[i] == collideableObjects_[j])
			{
				continue;
			}

			// get physics object B
			///////////////////////////////////////////////PhysicsObject* physicsObjectB = collideableObjects_[j];

			//StrongPtr<PhysicsObject> physicsObjectB = StrongPtr<PhysicsObject>(collideableObjects_[j]);
			PhysicsObject* physicsObjectB = collideableObjects_[j].GetObjectPtr();
			// get game object B
			const StrongPtr<GameObject> gameObjectB = physicsObjectB->GetGameObject().GetObjectPtr();
			// get B's AABB
			const AABB bAABB = gameObjectB->GetAABB();

			// calculate transform to convert object B to world coordinates

			Matrix4x4 matBRotation = Matrix4x4::GetRotationZ(gameObjectB.GetObjectPtr()->GetRotation());
			Matrix4x4 matBTranslation = Matrix4x4::GetTranslation(gameObjectB.GetObjectPtr()->GetPosition());
			Matrix4x4 matBToWorld = matBTranslation * matBRotation;

			// calculate transform to convert world to object B coordinates
			Matrix4x4 matWorldtoB(matBToWorld.GetInverse());

			// calculate transform to convert from A to B coordinates
			Matrix4x4 matAToB = matWorldtoB * matAToWorld;
			// calculate transform to convert from B to A coordinates
			Matrix4x4 matBToA(matAToB.GetInverse());

			bool isXSeparatedInB = false;
			bool isYSeparatedInB = false;

			float closeXinB = 0.0f;
			float openXinB = 0.0f;
			float closeYinB = 0.0f;
			float openYinB = 0.0f;

			// check for A in B's coordinate system
			{
				// calculate velocity of A relative to B
				const Vector2 relativeVelocityAToB = physicsObjectA->GetVelocity() - physicsObjectB->GetVelocity();

				// transform relative velocity (as a vector) to object B's coordinate system
				const Vector4 relativeVelocityWorldToB = matWorldtoB * Vector4(relativeVelocityAToB, 0.0f);

				// transform A's AABB to B's coordinate system
				const Vector4 ACenterInB = matAToB * Vector4(aAABB.center, 1.0f);
				const Vector4 AXExtentInB = matAToB * Vector4(aAABB.extents.x(), 0.0f, 0.0f, 0.0f);
				const Vector4 AYExtentInB = matAToB * Vector4(0.0f, aAABB.extents.y(), 0.0f, 0.0f);
				const Vector4 AExtentsInB(fabs(AXExtentInB.x()) + fabs(AYExtentInB.x()), fabs(AXExtentInB.y()) + fabs(AYExtentInB.y()), 0.0f, 0.0f);

				// for X axis
				{
					// treat zero velocities differently
					if (RoundedEqual(relativeVelocityWorldToB.x(), 0.0f))
					{
						// separation check without velocities
						//isXSeparatedInB = fabs(ACenterInB.x() - bAABB.center.x()) > AXExtentInB.x() + bAABB.extents.x();
						isXSeparatedInB = fabs(ACenterInB.x() - bAABB.center.x()) > AExtentsInB.x() + bAABB.extents.x();
					}
					else
					{
						// calculate separation close and open times
						closeXinB = (bAABB.center.x() - bAABB.extents.x() - ACenterInB.x() - AExtentsInB.x()) / relativeVelocityWorldToB.x();
						openXinB = (bAABB.center.x() + bAABB.extents.x() - ACenterInB.x() + AExtentsInB.x()) / relativeVelocityWorldToB.x();

						// close must be less than open
						// if not, swap them
						if (openXinB < closeXinB)
						{
							float swap = openXinB;
							openXinB = closeXinB;
							closeXinB = swap;
						}

						// if open < 0, the separation occurred in the past
						// if close > dt, the separation will occur in the future
						isXSeparatedInB = openXinB < 0 || closeXinB > dt;
					}

				} // for X axis

				// for Y axis, only if no separation was found on the X-axis
				if (!isXSeparatedInB)
				{
					// treat zero velocities differently
					if (RoundedEqual(relativeVelocityWorldToB.y(), 0.0f))
					{
						// separation check without velocities
						isYSeparatedInB = fabs(ACenterInB.y() - bAABB.center.y()) > AExtentsInB.y() + bAABB.extents.y();
					}
					else
					{
						// calculate separation close and open times
						closeYinB = (bAABB.center.y() - bAABB.extents.y() - ACenterInB.y() - AExtentsInB.y()) / relativeVelocityWorldToB.y();
						openYinB = (bAABB.center.y() + bAABB.extents.y() - ACenterInB.y() + AExtentsInB.y()) / relativeVelocityWorldToB.y();

						// t_close must be less than t_open
						// if not, swap them
						if (openYinB < closeYinB)
						{
							float swap = openYinB;
							openYinB = closeYinB;
							closeYinB = swap;
						}

						// if open < 0, the separation occurred in the past
						// if close > dt, the separation will occur in the future
						isYSeparatedInB = openYinB < 0 || closeYinB > dt;
					}

				} // for Y axis

			} // check for A in B's coordinate system    

			bool isXSeparatedInA = false;
			bool isYSeparatedInA = false;

			float closeXInA = 0.0f;
			float openXInA = 0.0f;
			float closeYInA = 0.0f;
			float openYInA = 0.0f;

			// check for B in A's coordinate system
			{
				// calculate velocity of B relative to A
				const Vector2 relativeVelocityBToA = physicsObjectB->GetVelocity() - physicsObjectA->GetVelocity();

				// transform relative velocity (as a vector) to A's coordinate system
				const Vector4 relativeVelocityWorldToA = matWorldToA * Vector4(relativeVelocityBToA, 0.0f);

				// transform B's AABB to A's coordinate system
				const Vector4 BCenterInA = matBToA * Vector4(bAABB.center, 1.0f);
				const Vector4 BXExtentInA = matBToA * Vector4(bAABB.extents.x(), 0.0f, 0.0f, 0.0f);
				const Vector4 BYExtentInA = matBToA * Vector4(0.0f, bAABB.extents.y(), 0.0f, 0.0f);
				const Vector4 BExtentsInA(fabs(BXExtentInA.x()) + fabs(BYExtentInA.x()), fabs(BXExtentInA.y()) + fabs(BYExtentInA.y()), 0.0f, 0.0f);

				// for X axis
				{
					// treat zero velocities differently
					if (RoundedEqual(relativeVelocityWorldToA.x(), 0.0f))
					{
						// separation check without velocities
						isXSeparatedInA = fabs(aAABB.center.x() - BCenterInA.x()) > aAABB.extents.x() + BExtentsInA.x();
					}
					else
					{
						// calculate separation close and open times
						closeXInA = (aAABB.center.x() - aAABB.extents.x() - BCenterInA.x() - BExtentsInA.x()) / relativeVelocityWorldToA.x();
						openXInA = (aAABB.center.x() + aAABB.extents.x() - BCenterInA.x() + BExtentsInA.x()) / relativeVelocityWorldToA.x();

						// close must be less than t_open
						// if not, swap them
						if (openXInA < closeXInA)
						{
							float t_swap = openXInA;
							openXInA = closeXInA;
							closeXInA = t_swap;
						}

						// if open < 0, the separation occurred in the past
						// if close > dt, the separation will occur in the future
						isXSeparatedInA = openXInA < 0 || closeXInA > dt;
					}
				}

				// for Y axis, only if no separation was found on the X axis
				if (!isXSeparatedInA)
				{
					// treat zero velocities differently
					if (RoundedEqual(relativeVelocityWorldToA.y(), 0.0f))
					{
						// separation check without velocities
						isYSeparatedInA = fabs(aAABB.center.y() - BCenterInA.y()) > aAABB.extents.y() + BExtentsInA.y();
					}
					else
					{
						// calculate separation close and open times
						closeYInA = (aAABB.center.y() - aAABB.extents.y() - BCenterInA.y() - BExtentsInA.y()) / relativeVelocityWorldToA.y();
						openYInA = (aAABB.center.y() + aAABB.extents.y() - BCenterInA.y() + BExtentsInA.y()) / relativeVelocityWorldToA.y();

						// close must be less than open
						// if not, swap them
						if (openYInA < closeYInA)
						{
							float swap = openYInA;
							openYInA = closeYInA;
							closeYInA = swap;
						}

						// if open < 0, the separation occurred in the past
						// if close > dt, the separation will occur in the future
						isYSeparatedInA = openYInA < 0 || closeYInA > dt;
					}

				}

			} // check for B in A's coordinate system

			// if separation
			if (!(isXSeparatedInB || isYSeparatedInB || isXSeparatedInA || isYSeparatedInA))
			{
				// find the latest t_close and the earliest t_open
				float closeLatest = GetMaxOfFour(closeXinB, closeYinB, closeXInA, closeYInA);
				float openEarliest = GetMinOfFour(openXinB, openYinB, openXInA, openYInA);


				// if the latest t_close was after the earliest t_open, there was continuity of separation
				if (closeLatest > openEarliest)
				{
					//no collision
				}
				else
				{
					//collision

					physicsObjectA->ApplyForce(physicsObjectA->GetVelocity() * -5.0f);
					physicsObjectB->ApplyForce(physicsObjectB->GetVelocity() * -5.0f);

				}
			}
			else
			{
				//no collision
			}

		}

	}

}

void ColliderSystem::AddPhysicsObject(WeakPtr<PhysicsObject>& poWeakPtr)
{

	// acquire a lock
	std::lock_guard<std::mutex> lock(colliderMutex_);

	// check if this object already exists
	if (std::find(collideableObjects_.begin(), collideableObjects_.end(), poWeakPtr) != collideableObjects_.end())
	{
		//LOG_ERROR("Collider is already tracking this physics object!");
		return;
	}
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];
	sprintf_s(Buffer, lenBuffer, "ADDDDDDDDDDDDDDDDING \n");
	OutputDebugStringA(Buffer);
	// add it to the list

	collideableObjects_.push_back(poWeakPtr);
	++num_physics_objects_;

	sprintf_s(Buffer, lenBuffer, "ADDDDDDDDDDDDDDDDDDDDDED \n");
	OutputDebugStringA(Buffer);
}

void ColliderSystem::RemovePhysicsObject(WeakPtr<PhysicsObject>& poWeakPtr)
{

	// acquire a lock
	std::lock_guard<std::mutex> lock(colliderMutex_);

	// check if this object exists
	auto it = std::find(collideableObjects_.begin(), collideableObjects_.end(), poWeakPtr);
	if (it == collideableObjects_.end())
	{
		//not found
		return;
	}

	collideableObjects_.erase(it);
	--num_physics_objects_;
}

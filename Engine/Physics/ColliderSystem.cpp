#include "Engine/Physics/ColliderSystem.h"
#include <cassert>
#include <Game\MonsterChaseGame.h>

// static member initialization
ColliderSystem* ColliderSystem::instance_ = nullptr;

ColliderSystem::ColliderSystem() : collideableObjectsAmount_(0)
{}

ColliderSystem::~ColliderSystem()
{
	collideableObjects_.clear();
	collideableObjectsAmount_ = 0;
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
	for (size_t i = 0; i < collideableObjectsAmount_; i++)
	{
		if (collideableObjects_[i].GetObjectPtr()->GetGameObject().GetObjectPtr()->GetIsActive()) {
			// get physics object A
			StrongPtr<PhysicsObject> physicsObjectA = StrongPtr<PhysicsObject>(collideableObjects_[i]);
			// get game object A
			StrongPtr<GameObject>gameObjectA(physicsObjectA->GetGameObject());

			// get A's AABB
			const AABB aAABB = gameObjectA->GetAABB();



			// calculate transform to convert from object A to world coordinates
			Matrix4x4 matARotation = Matrix4x4::GetRotationZ(gameObjectA.GetObjectPtr()->GetRotation());
			Matrix4x4 matATranslation = Matrix4x4::GetTranslation(gameObjectA.GetObjectPtr()->GetPosition());
			Matrix4x4 matAToWorld = matATranslation * matARotation;
			// calculate transform to convert world to object A coordinates
			Matrix4x4 matWorldToA(matAToWorld.GetInverse());

			for (size_t j = 0; j < collideableObjectsAmount_; j++)
			{
				// don't compute collisions with self
				if (collideableObjects_[i] == collideableObjects_[j])
				{
					continue;
				}

				// get physics object B
				StrongPtr<PhysicsObject> physicsObjectB = StrongPtr<PhysicsObject>(collideableObjects_[j]);
				// get game object B
				const StrongPtr<GameObject> gameObjectB(physicsObjectB->GetGameObject());
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

#pragma region check A in B coordinate
				bool isXSeparatedInB = false;
				bool isYSeparatedInB = false;

				float closeXinB = 0.0f;
				float openXinB = 0.0f;
				float closeYinB = 0.0f;
				float openYinB = 0.0f;


				// calculate velocity of A relative to B
				const Vector2 relativeVelocityAToB = physicsObjectA->GetVelocity() - physicsObjectB->GetVelocity();

				// transform relative velocity (as a vector) to object B's coordinate system
				const Vector4 relativeVelocityWorldToB = matWorldtoB * Vector4(relativeVelocityAToB, 0.0f, 0.0f);

				// transform A's AABB to B's coordinate system
				const Vector4 ACenterInB = matAToB * Vector4(aAABB.center, 0.0f, 1.0f);
				const Vector4 AXExtentInB = matAToB * Vector4(aAABB.extents.x(), 0.0f, 0.0f, 0.0f);
				const Vector4 AYExtentInB = matAToB * Vector4(0.0f, aAABB.extents.y(), 0.0f, 0.0f);
				const Vector4 AExtentsInB(fabs(AXExtentInB.x()) + fabs(AYExtentInB.x()), fabs(AXExtentInB.y()) + fabs(AYExtentInB.y()), 0.0f, 0.0f);

				// for X axis
				{
					// treat zero velocities differently
					if (RoundedEqual(relativeVelocityWorldToB.x(), 0.0f))
						//if (true)
					{
						// separation check without velocities
						//isXSeparatedInB = fabs(ACenterInB.x() - bAABB.center.x()) > AXExtentInB.x() + bAABB.extents.x();
						isXSeparatedInB = fabs(
							//							gameObjectA.GetObjectPtr()->GetPosition().x() +
							fabs(ACenterInB.x()) - bAABB.center.x()
							//							+ gameObjectB.GetObjectPtr()->GetPosition().x()
						) > AExtentsInB.x() + bAABB.extents.x();

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
				//---------if (!isXSeparatedInB)
				{
					// treat zero velocities differently
					if (RoundedEqual(relativeVelocityWorldToB.y(), 0.0f))
						//if (true)
					{
						// separation check without velocities
						isYSeparatedInB = fabs(
							//							gameObjectA.GetObjectPtr()->GetPosition().y() +
							fabs(ACenterInB.y()) - bAABB.center.y()
							//							+ gameObjectB.GetObjectPtr()->GetPosition().y()
						) > AExtentsInB.y() + bAABB.extents.y();

					}
					else
					{
						// calculate separation close and open times
						closeYinB = (bAABB.center.y() - bAABB.extents.y() - ACenterInB.y() - AExtentsInB.y()) / relativeVelocityWorldToB.y();
						openYinB = (bAABB.center.y() + bAABB.extents.y() - ACenterInB.y() + AExtentsInB.y()) / relativeVelocityWorldToB.y();

						// close must be less than open
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



				if (isXSeparatedInB && isYSeparatedInB) {
					//no collision
					//const size_t	lenBuffer = 65;
					//char			Buffer[lenBuffer];
					//sprintf_s(Buffer, lenBuffer, "NOOOOOT COLLIDING line 193 \n");
					//OutputDebugStringA(Buffer);
				}

#pragma endregion
#pragma region check B in A coordinate
				bool isXSeparatedInA = false;
				bool isYSeparatedInA = false;

				float closeXInA = 0.0f;
				float openXInA = 0.0f;
				float closeYInA = 0.0f;
				float openYInA = 0.0f;
				// calculate velocity of B relative to A
				const Vector2 relativeVelocityBToA = physicsObjectB->GetVelocity() - physicsObjectA->GetVelocity();

				// transform relative velocity (as a vector) to A's coordinate system
				const Vector4 relativeVelocityWorldToA = matWorldToA * Vector4(relativeVelocityBToA, 0.0f, 0.0f);

				// transform B's AABB to A's coordinate system
				const Vector4 BCenterInA = matBToA * Vector4(bAABB.center, 0.0f, 1.0f);
				const Vector4 BXExtentInA = matBToA * Vector4(bAABB.extents.x(), 0.0f, 0.0f, 0.0f);
				const Vector4 BYExtentInA = matBToA * Vector4(0.0f, bAABB.extents.y(), 0.0f, 0.0f);
				const Vector4 BExtentsInA(fabs(BXExtentInA.x()) + fabs(BYExtentInA.x()), fabs(BXExtentInA.y()) + fabs(BYExtentInA.y()), 0.0f, 0.0f);

				// for X axis
				{
					// treat zero velocities differently
					if (RoundedEqual(relativeVelocityWorldToA.x(), 0.0f))
						//if (true)
					{
						// separation check without velocities
						isXSeparatedInA = fabs(
							//							gameObjectB.GetObjectPtr()->GetPosition().x() +
							fabs(aAABB.center.x()) - BCenterInA.x()
							//							+ gameObjectA.GetObjectPtr()->GetPosition().x()
						) > aAABB.extents.x() + BExtentsInA.x();

					}
					else
					{
						// calculate separation close and open times
						closeXInA = (aAABB.center.x() - aAABB.extents.x() - BCenterInA.x() - BExtentsInA.x()) / relativeVelocityWorldToA.x();
						openXInA = (aAABB.center.x() + aAABB.extents.x() - BCenterInA.x() + BExtentsInA.x()) / relativeVelocityWorldToA.x();

						// close must be less than open
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
				//---------------if (!isXSeparatedInA)
				{
					// treat zero velocities differently
					if (RoundedEqual(relativeVelocityWorldToA.y(), 0.0f))
						//if (true)
					{
						// separation check without velocities
						isYSeparatedInA = fabs(
							//							gameObjectB.GetObjectPtr()->GetPosition().y() +
							fabs(aAABB.center.y()) - BCenterInA.y()
							//							+ gameObjectA.GetObjectPtr()->GetPosition().y()
						) > aAABB.extents.y() + BExtentsInA.y();

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

				if (isXSeparatedInA && isYSeparatedInA) {
					//no collision
					//const size_t	lenBuffer = 65;
					//char			Buffer[lenBuffer];
					//sprintf_s(Buffer, lenBuffer, "NOOOOOT COLLIDING line 295 \n");
					//OutputDebugStringA(Buffer);
				}
#pragma endregion




				///**
				// if separation
				if (!(isXSeparatedInB || isYSeparatedInB || isXSeparatedInA || isYSeparatedInA))
					//if (!(isXSeparatedInB == true && isYSeparatedInB == true && isXSeparatedInA == true && isYSeparatedInA == true))
				{
					// find the latest close and the earliest open
					float closeLatest = GetMaxOfFour(closeXinB, closeYinB, closeXInA, closeYInA);
					float openEarliest = GetMinOfFour(openXinB, openYinB, openXInA, openYInA);


					// if the latest close was after the earliest open, there was continuity of separation
					if (closeLatest > openEarliest)
					{
						//no collision
						//const size_t	lenBuffer = 65;
						//char			Buffer[lenBuffer];
						//sprintf_s(Buffer, lenBuffer, "NOOOOOT COLLIDING line 319 \n");
						//OutputDebugStringA(Buffer);
					}
					else
					{

						//collision
						//const size_t	lenBuffer = 65;
						//char			Buffer[lenBuffer];
						//sprintf_s(Buffer, lenBuffer, "COLLIDING line 327\n");
						//OutputDebugStringA(Buffer);

						Vector2 normal = Vector2::ZERO;
						if (RoundedEqual(closeLatest, closeXinB))
						{
							const Vector4 bXInWorld = matBToWorld.GetCol0();
							bXInWorld.Normalize();
							normal.set(bXInWorld.x(), bXInWorld.y());
							collided_objects_.push_back({ closeLatest, -normal,normal, physicsObjectA, physicsObjectB });
						}
						else if (RoundedEqual(closeLatest, closeYinB))
						{
							const Vector4 bYInWorld = matBToWorld.GetCol1();
							bYInWorld.Normalize();
							normal.set(bYInWorld.x(), bYInWorld.y());
							collided_objects_.push_back({ closeLatest, -normal,normal, physicsObjectA, physicsObjectB });
						}
						else if (RoundedEqual(closeLatest, closeXInA))
						{
							const Vector4 aXInWorld = matAToWorld.GetCol0();
							aXInWorld.Normalize();
							normal.set(aXInWorld.x(), aXInWorld.y());
							collided_objects_.push_back({ closeLatest, normal,-normal, physicsObjectA, physicsObjectB });
						}
						else if (RoundedEqual(closeLatest, closeYInA))
						{
							const Vector4 aYInWorld = matAToWorld.GetCol1();
							aYInWorld.Normalize();
							normal.set(aYInWorld.x(), aYInWorld.y());
							collided_objects_.push_back({ closeLatest, normal,-normal, physicsObjectA, physicsObjectB });
						}



					}
				}
				else
				{
					//const size_t	lenBuffer = 65;
					//char			Buffer[lenBuffer];
					//sprintf_s(Buffer, lenBuffer, "NOOOOOT COLLIDING line 339\n");
					//OutputDebugStringA(Buffer);
				}
				//**/
			}

		}
	}

	const size_t num_collided_objects = collided_objects_.size();

	for (size_t i = 0; i < num_collided_objects; ++i)
	{
		CollisionPair& collision_pair = collided_objects_[i];

		//StrongPtr<PhysicsObject>(collision_pair.objectA)->RespondToCollision(collision_pair.normalA);
		//StrongPtr<PhysicsObject>(collision_pair.objectB)->RespondToCollision(collision_pair.normalB);

		//collision_pair.objectA.GetObjectPtr()->GetGameObject().GetObjectPtr()->RespondToCollision(collision_pair.objectB.GetObjectPtr()->GetGameObject().GetObjectPtr());
		//collision_pair.objectB.GetObjectPtr()->GetGameObject().GetObjectPtr()->RespondToCollision(collision_pair.objectA.GetObjectPtr()->GetGameObject().GetObjectPtr());


		Game::MonsterChaseGame::GetInstance()->RespondToCollision(
			collision_pair.objectA.GetObjectPtr()->GetGameObject().GetObjectPtr(),
			collision_pair.objectB.GetObjectPtr()->GetGameObject().GetObjectPtr());

	}
	collided_objects_.clear();
}


void ColliderSystem::AddPhysicsObject(WeakPtr<PhysicsObject>& poWeakPtr)
{
	//only add if it is collideable
	if (!poWeakPtr.GetObjectPtr()->GetCollideable()) {
		return;
	}
	// acquire a lock
	std::lock_guard<std::mutex> lock(colliderMutex_);

	// check if this object already exists
	if (std::find(collideableObjects_.begin(), collideableObjects_.end(), poWeakPtr) != collideableObjects_.end())
	{
		return;
	}


	collideableObjects_.push_back(poWeakPtr);
	++collideableObjectsAmount_;

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
	--collideableObjectsAmount_;
}


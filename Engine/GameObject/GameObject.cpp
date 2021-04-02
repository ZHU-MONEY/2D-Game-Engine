#include "GameObject.h"
#include <Engine\EngineUtils.h>

static std::vector<StrongPtr<GameObject>> AllGameObjects;
static std::vector<StrongPtr<GameObject>> NewGameObjects;
static Engine::Mutex NewGameObjectMutex;

StrongPtr<GameObject> GameObject::Create()
{

	StrongPtr<GameObject> newGO = StrongPtr<GameObject>(new GameObject());
	AddNewGameObject(newGO);
	return newGO;
}

GameObject::GameObject() :
	position_(Vector2::ZERO),
	aabb_(AABB::ZERO),
	rotation_(0.0f)
{

}

GameObject::~GameObject()
{
}


GameObject::GameObject(const GameObject& other)
{
	position_ = other.position_;
	aabb_ = other.aabb_;
}


GameObject& GameObject::operator=(const GameObject& other)
{
	position_ = other.GetPosition();
	aabb_ = other.GetAABB();
	return *this;
}

void GameObject::CheckForNewGameObjects()
{
	Engine::ScopeLock Lock(NewGameObjectMutex);

	if (!NewGameObjects.empty())
	{
		for (StrongPtr<GameObject> p : NewGameObjects)
		{
			if (p)
			{
				//std::cout << "Moving " << p->GetName() << " to AllObjects.\n";
				AllGameObjects.push_back(p);
			}
		}

		NewGameObjects.clear();
	}
}

void GameObject::AddNewGameObject(StrongPtr<GameObject> i_pNewGameObject)
{
	if (i_pNewGameObject)
	{
		// Acquire a scoped lock on the mutex
		Engine::ScopeLock Lock(NewGameObjectMutex);

		NewGameObjects.push_back(i_pNewGameObject);
	}
}



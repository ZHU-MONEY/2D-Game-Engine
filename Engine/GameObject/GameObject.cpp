#include "GameObject.h"
#include <Engine\EngineUtils.h>
#include "Game/MonsterChaseGame.h"

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
	rotation_(0.0f),
	isStatic_(false),
	isActive_(true)
{

}

GameObject::~GameObject()
{

}


GameObject::GameObject(const GameObject& other)
{
	position_ = other.position_;
	aabb_ = other.aabb_;
	rotation_ = other.rotation_;
	isStatic_ = other.isStatic_;
	isActive_ = other.isActive_;
}


GameObject& GameObject::operator=(const GameObject& other)
{
	position_ = other.GetPosition();
	aabb_ = other.GetAABB();
	rotation_ = other.GetRotation();
	isStatic_ = other.GetIsStatic();
	isActive_ = other.GetIsActive();
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

void GameObject::AddNewGameObject(StrongPtr<GameObject> newGameObject)
{
	if (newGameObject)
	{
		// Acquire a scoped lock on the mutex
		Engine::ScopeLock Lock(NewGameObjectMutex);

		NewGameObjects.push_back(newGameObject);
	}
}

void GameObject::RespondToCollision(GameObject* other)
{

	if (Game::MonsterChaseGame::GetInstance()->GetPlayer().GetObjectPtr()==this) {
		return;
	}

	if (Game::MonsterChaseGame::GetInstance()->GetTarget1().GetObjectPtr() == this ||
		Game::MonsterChaseGame::GetInstance()->GetTarget2().GetObjectPtr() == this ||
		Game::MonsterChaseGame::GetInstance()->GetTarget3().GetObjectPtr() == this) {
		this->SetIsActive(false);
	}
	//this is a very broken way of getting things done
	if (this->isStatic_) {
		if (other->GetIsStatic())
			return;
		else if (other == Game::MonsterChaseGame::GetInstance()->GetPlayer().GetObjectPtr())
			other->SetIsActive(false);
	}
}

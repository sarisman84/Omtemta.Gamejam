#pragma once
#include <List.h>
#include <atomic>
#include <thread>
#include <functional>
#include "Entity.h"

using namespace CommonUtilities;


class CGameWorld;

class EntityManager
{
public:
	~EntityManager();
	EntityManager(CGameWorld* aWorld, std::function<void(EntityManager*)> aUpdateEvent);
	void AddEntity(Entity* anEntityToAdd);
	void AddEntities(List<Entity*> aNewSetOfEntities);
	void RemoveEntity(Entity* anEntityToRemove);

	void UpdateEntities();
	void RenderEntities();


	Entity* GetEntityWithTag(const char* aTag);

private:
	void CheckCollisions(Entity* anEntityToCheck);
	std::function<void(EntityManager*)> myUpdateEvent;

	std::thread myUpdateThread;
	std::atomic<bool> myUpdateFlag;

	List<Entity*> myCurrentEntities;
	Tga2D::CSpriteDrawer* myDrawer;
	CGameWorld* myWorld;
};


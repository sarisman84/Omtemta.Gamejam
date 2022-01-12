#pragma once
#include <List.h>
#include <atomic>
#include <thread>
#include "Entity.h"

using namespace CommonUtilities;


class CGameWorld;

class EntityManager
{
public:
	~EntityManager();
	EntityManager(CGameWorld* aWorld);
	void AddEntity(Entity* anEntityToAdd);
	void RemoveEntity(Entity* anEntityToRemove);

	void UpdateEntities();
	void RenderEntities();
private:
	void CheckCollisions(Entity* anEntityToCheck);


	std::thread myUpdateThread;
	std::atomic<bool> myUpdateFlag;

	List<Entity*> myCurrentEntities;
	Tga2D::CSpriteDrawer* myDrawer;
	CGameWorld* myWorld;
};


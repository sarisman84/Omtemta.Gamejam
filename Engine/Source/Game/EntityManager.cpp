#include "stdafx.h"
#include "EntityManager.h"
#include <tga2d/d3d/direct_3d.h>
#include "VectorUtilities.h"
#include "GameWorld.h"
EntityManager::~EntityManager()
{
	for (auto& entity : myCurrentEntities)
	{
		if (!entity) continue;
		delete entity;
	}
	myCurrentEntities.Clear();
}
EntityManager::EntityManager(CGameWorld* aWorld, std::function<void(EntityManager*)> aUpdateEvent)
{
	myWorld = aWorld;
	myDrawer = &Tga2D::CEngine::GetInstance()->GetDirect3D().GetSpriteDrawer();
	myUpdateThread = std::thread([&]()
		{
			float refreshRate = 1.0f / 120.0f;
			float curRate = 0;
			while (true)
			{
				curRate += myWorld->GetTimeManager()->GetDeltaTime_Sec();
				if (curRate >= refreshRate)
				{
					//std::cout << "Updated Called!" << std::endl;
					UpdateEntities();

					curRate = 0;
				}

			}
		});

	myUpdateEvent = aUpdateEvent;
}

void EntityManager::AddEntity(Entity* anEntityToAdd)
{
	for (auto& entity : myCurrentEntities)
	{
		if (entity == anEntityToAdd) return;
	}
	myCurrentEntities.Add(anEntityToAdd);
}

void EntityManager::AddEntities(List<Entity*> aNewSetOfEntities)
{
	for (auto& newEntity : aNewSetOfEntities)
	{
		AddEntity(newEntity);
	}
}

void EntityManager::RemoveEntity(Entity* anEntityToRemove)
{
	for (auto& entity : myCurrentEntities)
	{
		if (entity == anEntityToRemove)
		{
			delete entity;
			myCurrentEntities.Remove(entity);
			break;
		}
	}
}

void EntityManager::UpdateEntities()
{
	if (!myUpdateFlag) return;
	for (int i = 0; i < myCurrentEntities.Count(); i++)
	{
		if (i >= myCurrentEntities.Count()) return;

		Entity* entity = myCurrentEntities[i];

		if (!myUpdateFlag) return;
		if (!entity) continue;

		entity->UpdateEntity(myWorld);
		CheckCollisions(entity);
	}
}

void EntityManager::RenderEntities()
{
	myUpdateFlag = false;

	for (int i = 0; i < myCurrentEntities.Count(); i++)
	{
		if (i >= myCurrentEntities.Count()) return;
		Entity* entity = myCurrentEntities[i];

		if (!entity) continue;
		entity->Render(myDrawer);
	}
	myUpdateFlag = true;
}

Entity* EntityManager::GetEntityWithTag(const char* aTag)
{
	for (auto& entity : myCurrentEntities)
	{
		if (!myUpdateFlag) return nullptr;
		if (!entity) continue;

		if (entity->IsOfTag(aTag)) return entity;
	}
	return nullptr;
}

void EntityManager::CheckCollisions(Entity* anEntityToCheck)
{
	for (int i = 0; i < myCurrentEntities.Count(); i++)
	{
		if (i >= myCurrentEntities.Count()) return;

		Entity* entity = myCurrentEntities[i];

		if (!myUpdateFlag) return;
		if (!entity || entity == anEntityToCheck) continue;
		anEntityToCheck->CheckCollision(myWorld, entity);

	}
}

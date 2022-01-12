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
EntityManager::EntityManager(CGameWorld* aWorld)
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
}

void EntityManager::AddEntity(Entity* anEntityToAdd)
{
	for (auto& entity : myCurrentEntities)
	{
		if (entity == anEntityToAdd) return;
	}
	myCurrentEntities.Add(anEntityToAdd);
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
	for (auto& entity : myCurrentEntities)
	{
		if (!myUpdateFlag) return;
		if (!entity) continue;
		entity->UpdateEntity(myWorld);
	}
}

void EntityManager::RenderEntities()
{
	myUpdateFlag = false;

	for (auto& entity : myCurrentEntities)
	{

		if (!entity) continue;
		entity->Render(myDrawer);
	}
	myUpdateFlag = true;
}

void EntityManager::CheckCollisions(Entity* anEntityToCheck)
{
	for (auto& entity : myCurrentEntities)
	{
		if (!myUpdateFlag) return;
		if (!entity || entity == anEntityToCheck || Vector2<float>::Distance(Convert::ToCustom(anEntityToCheck->Transform().myPosition), Convert::ToCustom(entity->Transform().myPosition)) > 0.25f) continue;
		anEntityToCheck->CheckCollision(entity);

	}
}

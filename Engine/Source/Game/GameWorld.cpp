#include "stdafx.h"
#include "GameWorld.h"
#include <tga2d/engine.h>
#include <tga2d/error/error_manager.h>
#include <tga2d/d3d/direct_3d.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/drawers/sprite_drawer.h>
#include <tga2d/texture/texture_manager.h>

CGameWorld::CGameWorld()
{
	myManager = nullptr;
}

CGameWorld::~CGameWorld() 
{
	delete myManager;
}

void CGameWorld::Init()  
{
	myManager = new EntityManager(this);
	Entity* player = myFactory.CreateEntity(EntityTypeIndex::Player);
	myManager->AddEntity(player);

	player->Transform().myPosition = { 0.5f, 0.9f };
	player->Transform().mySize = { 0.1f, 0.025f };
}

void CGameWorld::Update(float /*aTimeDelta*/)
{ 	

}

void CGameWorld::Render()
{
	myManager->RenderEntities();
}

CommonUtilities::Input* CGameWorld::GetUserInput()
{
	return myUserInput;
}

CommonUtilities::Timer* CGameWorld::GetTimeManager()
{
	return myTimeManager;
}

void CGameWorld::SetUserInput(CommonUtilities::Input* anInputManager)
{
	myUserInput = anInputManager;
}

void CGameWorld::SetTimeManager(CommonUtilities::Timer* anTimeManager)
{
	myTimeManager = anTimeManager;
}

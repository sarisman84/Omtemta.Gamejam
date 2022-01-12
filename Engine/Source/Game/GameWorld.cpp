#include "stdafx.h"
#include "GameWorld.h"
#include <tga2d/engine.h>
#include <tga2d/error/error_manager.h>
#include <tga2d/d3d/direct_3d.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/drawers/sprite_drawer.h>
#include <tga2d/texture/texture_manager.h>
#include "VectorUtilities.h"
#include "EntityBehaviours.h"

CGameWorld::CGameWorld()
{
	myManager = nullptr;
}

CGameWorld::~CGameWorld()
{
	delete myManager;
	delete myCurrentScore;
}

void CGameWorld::Init()
{
	myManager = new EntityManager(this, [this](EntityManager* /*aManager*/) { Update(0); });
	Entity* player = myFactory.CreateEntity(EntityTypeIndex::Player);
	Entity* ball = myFactory.CreateEntity(EntityTypeIndex::Player_Ball);

	myManager->AddEntity(player);
	myManager->AddEntity(ball);

	player->SetValue<int>(PLAYER_SCORE, 0);

	player->SetValue<bool>(GAME_END, false);
	player->GetSize() = { (int)(100 * SCREENSCALE_X), 25 };
	player->GetPosition() = { static_cast<int>(SCREEN.x) / 2, (static_cast<int>(SCREEN.y) - player->GetSize().y) };


	ball->SetValue<Vector2Pixel>(BALL_VEL, { 0,-10 });
	ball->SetValue<bool>(BALL_MOVE, false);


	ball->GetPosition() = { static_cast<int>(SCREEN.x) / 2,static_cast<int>(SCREEN.y) / 2 };
	ball->GetSize() = { (int)(25 * SCREENSCALE_X), 25 };

	myCurrentScore = new Tga2D::CText();
	myCurrentScore->SetPosition({ 0.5f, 0.1f });
	myCurrentScore->SetScale(0.5f);

	myManager->AddEntities({
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2), (static_cast<int>(SCREEN.y) / 2) - 100}),
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2) - 55, (static_cast<int>(SCREEN.y) / 2) - 100}),
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2) + 55, (static_cast<int>(SCREEN.y) / 2) - 100}),
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2) - 105, (static_cast<int>(SCREEN.y) / 2) - 100}),
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2) + 105, (static_cast<int>(SCREEN.y) / 2) - 100}),
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2) - 155, (static_cast<int>(SCREEN.y) / 2) - 100}),
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2) + 155, (static_cast<int>(SCREEN.y) / 2) - 100}),

		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2), (static_cast<int>(SCREEN.y) / 2) - 130}),
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2) - 55, (static_cast<int>(SCREEN.y) / 2) - 130}),
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2) + 55, (static_cast<int>(SCREEN.y) / 2) - 130}),
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2) - 105, (static_cast<int>(SCREEN.y) / 2) - 130}),
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2) + 105, (static_cast<int>(SCREEN.y) / 2) - 130}),
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2) - 155, (static_cast<int>(SCREEN.y) / 2) - 130}),
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2) + 155, (static_cast<int>(SCREEN.y) / 2) - 130}),

		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2), (static_cast<int>(SCREEN.y) / 2) - 70}),
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2) - 55, (static_cast<int>(SCREEN.y) / 2) - 70}),
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2) + 55, (static_cast<int>(SCREEN.y) / 2) - 70}),
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2) - 105, (static_cast<int>(SCREEN.y) / 2) - 70}),
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2) + 105, (static_cast<int>(SCREEN.y) / 2) - 70}),
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2) - 155, (static_cast<int>(SCREEN.y) / 2) - 70}),
		myFactory.CreateEntity(EntityTypeIndex::Red_Brick)->SetSize({(int)(50 * SCREENSCALE_X), 25})->SetPosition({(static_cast<int>(SCREEN.x) / 2) + 155, (static_cast<int>(SCREEN.y) / 2) - 70}),


		});
}

void CGameWorld::Update(float /*aTimeDelta*/)
{
	if (myPlayer->GetValue<bool>(GAME_END))
	{
		exit(EXIT_SUCCESS);
	}
	else
	{
		myCurrentScore->SetText(std::to_string(myPlayer->GetValue<int>(PLAYER_SCORE)).c_str());
	}
}

void CGameWorld::Render()
{
	myManager->RenderEntities();
	myCurrentScore->Render();
}

CommonUtilities::Input* CGameWorld::GetUserInput()
{
	return myUserInput;
}

CommonUtilities::Timer* CGameWorld::GetTimeManager()
{
	return myTimeManager;
}

EntityManager* CGameWorld::GetEntityManager()
{
	return myManager;
}

EntityFactory& CGameWorld::GetEntityFactory()
{
	return myFactory;
}



void CGameWorld::SetUserInput(CommonUtilities::Input* anInputManager)
{
	myUserInput = anInputManager;
}

void CGameWorld::SetTimeManager(CommonUtilities::Timer* anTimeManager)
{
	myTimeManager = anTimeManager;
}

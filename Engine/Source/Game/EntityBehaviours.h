#pragma once
#include "Entity.h"
#include "GameWorld.h"
#include <UtilityFunctions.h>

class PlayerLogistics
{
public:
	_inline static void Update(CGameWorld* aWorld, Entity* aSelf)
	{

		aSelf->Transform().myPosition += { aWorld->GetUserInput()->GetAxisRaw(Axis::Horizontal) * 0.01f, 0 };
		aSelf->Transform().myPosition = {
			CommonUtilities::Clamp(0.0f + aSelf->Transform().mySize.x / 2.0f,1.0f - aSelf->Transform().mySize.x / 2.0f,aSelf->Transform().myPosition.x),aSelf->Transform().myPosition.y
		};
	}




};


class BrickLogistics
{
public:
	_inline static void OnCollision(Entity* /*someOtherEntity*/)
	{

	}
};


class BallLogistics
{
public:
	_inline static void Update(CGameWorld* /*aWorld*/, Entity* /*aSelf*/)
	{

	}

	_inline static void OnCollision(Entity* /*someOtherEntity*/)
	{

	}
};


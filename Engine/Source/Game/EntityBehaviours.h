#pragma once
#include "Entity.h"
#include "GameWorld.h"
#include <UtilityFunctions.h>
#include "VectorUtilities.h"

#define PBALL "P_Ball"
#define PLAYER "Player_Avatar"
#define PLAYER_SCORE "Player_Score"
#define GAME_END "Game_Over"


#define BALL_VEL "currentVelocity"
#define BALL_MOVE "isMoving"

#define WALL_WIDTH 50
#define PLAYER_CENTER_WIDTH 10

using namespace CommonUtilities;


class Player
{
public:
	Player() = default;
	_inline static void Update(CGameWorld* aWorld, Entity* aSelf)
	{

		aSelf->GetPosition() += { static_cast<int>(aWorld->GetUserInput()->GetAxisRaw(Axis::Horizontal) * 15), 0 };
		aSelf->GetPosition() = {
			CommonUtilities::Clamp(0 + aSelf->GetSize().x / 2,static_cast<int>(SCREEN.x) - aSelf->GetSize().x / 2, aSelf->GetPosition().x),aSelf->GetPosition().y
		};
	}




};


class Brick
{
public:
	_inline static void OnCollision(CGameWorld* aWorld, Entity* aSelf, Entity* someOtherEntity)
	{
		if (someOtherEntity->IsOfTag(PBALL))
		{
			Vector2Pixel curVel = someOtherEntity->GetValue<Vector2Pixel>(BALL_VEL);
			std::cout << "A Brick collided with a Ball!" << std::endl;

			if (someOtherEntity->GetPosition().y < aSelf->GetPosition().y)
			{
				curVel.y = CommonUtilities::Abs(curVel.y);
				curVel.y += 1;
				curVel.y *= -1;
			}
			else if (someOtherEntity->GetPosition().y > aSelf->GetPosition().y)
			{
				curVel.y = CommonUtilities::Abs(curVel.y);
				curVel.y += 1;
				curVel.y *= 1;
			}
			else if (someOtherEntity->GetPosition().x < aSelf->GetPosition().x)
			{
				curVel.x = CommonUtilities::Abs(curVel.x);
				curVel.x += 1;
				curVel.x *= -1;
			}
			else if (someOtherEntity->GetPosition().x > aSelf->GetPosition().x)
			{
				curVel.x = CommonUtilities::Abs(curVel.x);
				curVel.x += 1;
				curVel.x *= 1;
			}

			someOtherEntity->SetValue<Vector2Pixel>(BALL_VEL, curVel);

			Entity* player = aWorld->GetEntityManager()->GetEntityWithTag(PLAYER);
			if (player)
			{
				player->SetValue<int>(PLAYER_SCORE, player->GetValue<int>(PLAYER_SCORE) + 1);
				std::cout << "Player earned a point! ";
				std::cout << "Player Score: " << player->GetValue<int>(PLAYER_SCORE) << std::endl;
			}
				


			aWorld->GetEntityManager()->RemoveEntity(aSelf);
			return;


		}
	}
};


class Ball
{
public:
	Ball() = default;


	_inline static void Update(CGameWorld* aWorld, Entity* aSelf)
	{
		//Todo: 
		/*
		 -Add linear velocity
		 -Make it bounce.
		*/





		Vector2Pixel curVelocity = aSelf->GetValue<Vector2Pixel>(BALL_VEL);

		if (aSelf->GetPosition().y + aSelf->GetSize().y / 2 < WALL_WIDTH)
		{
			curVelocity.y *= -1; //Invert the y velocity should it bounce on the ceiling.
		}

		if (aSelf->GetPosition().x + aSelf->GetSize().x / 2 < WALL_WIDTH ||
			aSelf->GetPosition().x - aSelf->GetSize().x / 2 > (int)SCREEN.x - WALL_WIDTH)
		{
			curVelocity.x *= -1; //Invert the x velocity should it bounce of the sides.
		}


		if (aSelf->GetPosition().y - aSelf->GetSize().y / 2 > (int)SCREEN.y)
		{
			std::cout << "Player Lost!" << std::endl;
			aWorld->GetEntityManager()->GetEntityWithTag(PLAYER)->SetValue(GAME_END, true);
			aWorld->GetEntityManager()->RemoveEntity(aSelf);
			return;
		}


		aSelf->SetValue(BALL_VEL, curVelocity);

		aSelf->SetPosition(Vector2Pixel(aSelf->GetPosition().x + curVelocity.x, aSelf->GetPosition().y + curVelocity.y));







	}

	_inline static void OnCollision(CGameWorld* /*aWorld*/, Entity* aSelf, Entity* someOtherEntity)
	{
		if (someOtherEntity->IsOfTag(PLAYER))
		{
			/*std::cout << "Ball Collided with player!" << std::endl;*/
			Vector2Pixel curVelocity = aSelf->GetValue<Vector2Pixel>(BALL_VEL);
			curVelocity.y *= -1;


			curVelocity.x +=
				aSelf->GetPosition().x > someOtherEntity->GetPosition().x - PLAYER_CENTER_WIDTH / 2 ? 5 :
				aSelf->GetPosition().x < someOtherEntity->GetPosition().x + PLAYER_CENTER_WIDTH / 2 ? -5 : 0;


			aSelf->SetValue<Vector2Pixel>(BALL_VEL, curVelocity);
		}
	}


private:


};


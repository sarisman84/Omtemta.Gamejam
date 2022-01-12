#pragma once
#include "EntityFactory.h"
#include "EntityManager.h"

#include <tga2d/text/text.h>


#include <Input.h>
#include <Timer.h>

namespace Tga2D
{
	class CTexture;
}

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta); 
	void Render();

	CommonUtilities::Input* GetUserInput();
	CommonUtilities::Timer* GetTimeManager();
	EntityManager* GetEntityManager();
	EntityFactory& GetEntityFactory();




	void SetUserInput(CommonUtilities::Input* anInputManager);
	void SetTimeManager(CommonUtilities::Timer* anTimeManager);

private:
	Tga2D::CText* myCurrentScore;
	Entity* myPlayer;
	CommonUtilities::Input* myUserInput;
	CommonUtilities::Timer* myTimeManager;
	EntityManager* myManager;
	EntityFactory myFactory;
};
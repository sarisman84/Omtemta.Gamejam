#pragma once
#include "EntityFactory.h"
#include "EntityManager.h"

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

	void SetUserInput(CommonUtilities::Input* anInputManager);
	void SetTimeManager(CommonUtilities::Timer* anTimeManager);

private:
	CommonUtilities::Input* myUserInput;
	CommonUtilities::Timer* myTimeManager;
	EntityManager* myManager;
	EntityFactory myFactory;
};
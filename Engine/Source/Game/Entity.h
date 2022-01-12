#pragma once
#include "EntityType.h"
#include <tga2d/engine.h>
#include <tga2d/error/error_manager.h>
#include <tga2d/d3d/direct_3d.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/drawers/sprite_drawer.h>

#include <Vector2.h>
#include <map>
#include <any>
#include <typeindex>
#include <typeinfo>


typedef CommonUtilities::Vector2< int> Vector2Pixel;
typedef CommonUtilities::Vector2<float> Vector2Abs;
typedef Tga2D::SSpriteInstanceData SpriteObject;
typedef Tga2D::SSpriteSharedData SpriteMaterial;


class CGameWorld;

class Entity
{
public:
	Entity(EntityType* aType);
	EntityType* GetType();
	const EntityType* GetType() const;
	void CheckCollision(CGameWorld* aWorld, Entity* someOtherEntity);
	void UpdateEntity(CGameWorld* aWorld);
	void Render(Tga2D::CSpriteDrawer* aDrawer);
	Vector2Pixel& GetPosition();
	Vector2Pixel& GetSize();




	Entity* SetPosition(Vector2Pixel aPosition);
	Entity* SetSize(Vector2Pixel aPosition);

	const bool IsOfTag(const char* aTag);

	template<typename T>
	T GetValue(const char* aValueToEdit)
	{
		//This is based of this answer: https://stackoverflow.com/a/50956105

		
		return std::any_cast<T>(myRegisteredValues[aValueToEdit]);
	}


	template<typename T>
	void SetValue(const char* aValueToEdit, T aValueToSet)
	{
		
		//This is based of this answer: https://stackoverflow.com/a/50956105
		myRegisteredValues[aValueToEdit] = aValueToSet;
	}


private:

	//This is based of this answer: https://stackoverflow.com/a/50956105
	std::map<const char*, std::any> myRegisteredValues;


	const bool AABBCheck(Entity* someOtherEntity);

	Vector2Pixel mySize;
	Vector2Pixel myPosition;


	Vector2Abs PixelToAbsValue(Vector2Pixel aPixelValue);

	SpriteObject myTransform;
	SpriteMaterial myMaterial;


	EntityType* myType;
};


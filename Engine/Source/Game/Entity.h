#pragma once
#include "EntityType.h"
#include <tga2d/engine.h>
#include <tga2d/error/error_manager.h>
#include <tga2d/d3d/direct_3d.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/drawers/sprite_drawer.h>

#include <Vector2.h>

typedef CommonUtilities::Vector2<unsigned int> Vector2Pixel;
typedef CommonUtilities::Vector2<float> Vector2Abs;
typedef Tga2D::SSpriteInstanceData SpriteTransform;
typedef Tga2D::SSpriteSharedData SpriteMaterial;


class CGameWorld;

class Entity
{
public:
	Entity(EntityType* aType);
	EntityType* GetType();
	const EntityType* GetType() const;
	void CheckCollision(Entity* someOtherEntity);
	void UpdateEntity(CGameWorld* aWorld);
	void Render(Tga2D::CSpriteDrawer* aDrawer);
	SpriteTransform& Transform();
	SpriteMaterial& Material();
private:
	Vector2Pixel mySize;
	Vector2Pixel myPosition;


	Vector2Abs PixelToAbsValue(Vector2Pixel aPixelValue);

	SpriteTransform myTransform;
	SpriteMaterial myMaterial;
	

	EntityType* myType;
};


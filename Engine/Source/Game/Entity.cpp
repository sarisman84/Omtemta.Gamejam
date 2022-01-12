#include "stdafx.h"
#include "Entity.h"
#include <tga2d/texture/texture_manager.h>
#include "Debugger.h"

Entity::Entity(EntityType* aType)
{
	myType = aType;
	myMaterial = {};
	myTransform = {};

	myMaterial.myTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture(myType->GetTexturePath());
}

EntityType* Entity::GetType()
{
	return myType;
}

const EntityType* Entity::GetType() const
{
	return myType;
}

void Entity::CheckCollision(Entity* someOtherEntity)
{
	//AABB impl
	bool hasCollided = false;

	if (hasCollided)
	{
		CollisionEvent colEvent = myType->OnCollisionEvent();
		if (colEvent)
			colEvent(someOtherEntity);
	}

}

void Entity::UpdateEntity(CGameWorld* aWorld)
{
	UpdateEvent updateEvent = myType->OnUpdate();
	if (updateEvent)
		updateEvent(aWorld,this);
}

void Entity::Render(Tga2D::CSpriteDrawer* aDrawer)
{
	if (!aDrawer)
	{
		ErrorHandler::CustomLog("Drawer Pointer is invalid!", this);
		return;
	}

	aDrawer->Draw(myMaterial, myTransform);
}

SpriteTransform& Entity::Transform()
{
	return myTransform;
}

SpriteMaterial& Entity::Material()
{
	return myMaterial;
}

Vector2Abs Entity::PixelToAbsValue(Vector2Pixel aPixelValue)
{
	Tga2D::Vector2ui res = Tga2D::CEngine::GetInstance()->GetTargetSize();
	float x = static_cast<float>(aPixelValue.x / res.x);
	float y = static_cast<float>(aPixelValue.y / res.y);
	return Vector2Abs(x, y);
}

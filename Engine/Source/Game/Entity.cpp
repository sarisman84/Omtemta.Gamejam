#include "stdafx.h"
#include "Entity.h"
#include <tga2d/texture/texture_manager.h>
#include "Debugger.h"
#include "VectorUtilities.h"

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

void Entity::CheckCollision(CGameWorld* aWorld, Entity* someOtherEntity)
{
	//AABB impl
	bool hasCollided = AABBCheck(someOtherEntity);

	if (hasCollided)
	{
		CollisionEvent colEvent = myType->OnCollisionEvent();
		if (colEvent)
			colEvent(aWorld, this, someOtherEntity);
	}

}

void Entity::UpdateEntity(CGameWorld* aWorld)
{
	UpdateEvent updateEvent = myType->OnUpdate();
	if (updateEvent)
		updateEvent(aWorld, this);
}

void Entity::Render(Tga2D::CSpriteDrawer* aDrawer)
{
	if (!aDrawer)
	{
		ErrorHandler::CustomLog("Drawer Pointer is invalid!", this);
		return;
	}

	myTransform.myPosition = Convert::ToTga(PixelToAbsValue(myPosition));
	myTransform.mySize = Convert::ToTga(PixelToAbsValue(mySize));

	aDrawer->Draw(myMaterial, myTransform);
}

Vector2Pixel& Entity::GetPosition()
{
	return myPosition;
}

Vector2Pixel& Entity::GetSize()
{
	return mySize;
}

Entity* Entity::SetPosition(Vector2Pixel aPosition)
{
	myPosition = aPosition;
	return this;
}

Entity* Entity::SetSize(Vector2Pixel aSize)
{
	mySize = aSize;
	return this;
}



const bool Entity::IsOfTag(const char* aTag)
{
	return myType->GetTag() == aTag;
}



const bool Entity::AABBCheck(Entity* someOtherEntity)
{
	bool hasCollidedX = myPosition.x <= someOtherEntity->myPosition.x + someOtherEntity->mySize.x &&
		myPosition.x + mySize.x >= someOtherEntity->myPosition.x;

	bool hasCollidedY = myPosition.y <= someOtherEntity->myPosition.y + someOtherEntity->mySize.y &&
		myPosition.y + mySize.y >= someOtherEntity->myPosition.y;

	return hasCollidedX && hasCollidedY;
}

Vector2Abs Entity::PixelToAbsValue(Vector2Pixel aPixelValue)
{
	Tga2D::Vector2ui res = Tga2D::CEngine::GetInstance()->GetTargetSize();
	float x = ((float)aPixelValue.x / (float)res.x);
	float y = ((float)aPixelValue.y / (float)res.y);
	return Vector2Abs(x, y);
}

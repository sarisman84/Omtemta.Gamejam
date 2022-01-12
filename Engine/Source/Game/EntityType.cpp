#include "stdafx.h"
#include "EntityType.h"

EntityType::EntityType(const char* aTexture, CollisionEvent anCollisionEvent) : EntityType(aTexture, "", anCollisionEvent, nullptr)
{
}

EntityType::EntityType(const char* aTexture, CollisionEvent anCollisionEvent, UpdateEvent anUpdateEvent) : EntityType(aTexture, "", anCollisionEvent, anUpdateEvent)
{

}

EntityType::EntityType(const char* aTexture, const char* aTag, CollisionEvent anCollisionEvent) : EntityType(aTexture, aTag, anCollisionEvent, nullptr)
{

}



EntityType::EntityType(const char* aTexture, const char* aTag, CollisionEvent anCollisionEvent, UpdateEvent anUpdateEvent)
{

	myOnCollisionEvent = anCollisionEvent;
	myUpdateEvent = anUpdateEvent;
	myTexture = aTexture;
	myTag = aTag;
}

CollisionEvent& EntityType::OnCollisionEvent()
{
	return myOnCollisionEvent;
}

UpdateEvent& EntityType::OnUpdate()
{
	return myUpdateEvent;
}



const char* EntityType::GetTexturePath() const
{
	return myTexture;
}

const char* EntityType::GetTag() const
{
	return myTag;
}

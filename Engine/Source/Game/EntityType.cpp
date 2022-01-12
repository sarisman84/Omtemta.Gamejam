#include "stdafx.h"
#include "EntityType.h"

EntityType::EntityType(const char* aTexture, CollisionEvent anCollisionEvent, UpdateEvent anUpdateEvent)
{
    myOnCollisionEvent = anCollisionEvent;
    myUpdateEvent = anUpdateEvent;
    myTexture = aTexture;
}

std::function<void(Entity*)>& EntityType::OnCollisionEvent()
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

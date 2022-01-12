#include "stdafx.h"
#include "EntityFactory.h"
#include "EntityBehaviours.h"

EntityFactory::EntityFactory()
{
	myRegisteredTypes[EntityTypeIndex::Player] = EntityType("Sprites/paddle.dds", nullptr, PlayerLogistics::Update);
	myRegisteredTypes[EntityTypeIndex::Red_Brick] = EntityType("Sprites/redBlock.dds", BrickLogistics::OnCollision);
	myRegisteredTypes[EntityTypeIndex::Player_Ball] = EntityType("Sprites/Ball.dds", BallLogistics::OnCollision, BallLogistics::Update);
}

Entity* EntityFactory::CreateEntity(const EntityTypeIndex aType)
{
	return new Entity(&myRegisteredTypes[aType]);
}

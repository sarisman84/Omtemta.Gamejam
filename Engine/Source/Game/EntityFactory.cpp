#include "stdafx.h"
#include "EntityFactory.h"
#include "EntityBehaviours.h"

EntityFactory::EntityFactory()
{
	myRegisteredTypes[EntityTypeIndex::Player] = EntityType("Sprites/paddle.dds", PLAYER, nullptr, Player::Update);
	myRegisteredTypes[EntityTypeIndex::Red_Brick] = EntityType("Sprites/redBlock.dds", Brick::OnCollision);
	myRegisteredTypes[EntityTypeIndex::Player_Ball] = EntityType("Sprites/Ball.dds", PBALL, Ball::OnCollision, Ball::Update);
}

Entity* EntityFactory::CreateEntity(const EntityTypeIndex aType)
{
	return new Entity(&myRegisteredTypes[aType]);
}

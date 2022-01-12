#pragma once
#include "Entity.h"
#include "EntityType.h"
#include <map>

class EntityFactory
{
public:
	EntityFactory();
	EntityFactory(const EntityFactory& aVal) = delete;
	EntityFactory& operator=(const EntityFactory& aVal) = delete;
	Entity* CreateEntity(const EntityTypeIndex aType);
private:
	std::map<EntityTypeIndex, EntityType> myRegisteredTypes;
};


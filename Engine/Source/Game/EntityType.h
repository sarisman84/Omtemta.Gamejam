#pragma once
#include <functional>





enum class EntityTypeIndex
{
	Player,
	Player_Ball,
	Red_Brick,
	Blue_Brick,
	Green_Brick
};

class Entity;
class CGameWorld;
typedef std::function<void(Entity*)> CollisionEvent;
typedef std::function<void(CGameWorld*, Entity*)> UpdateEvent;


class EntityType
{
public:
	EntityType() = default;
	EntityType(const char* myTexture, CollisionEvent anCollisionEvent, UpdateEvent anUpdateEvent = nullptr);
	CollisionEvent& OnCollisionEvent();
	UpdateEvent& OnUpdate();
	const char* GetTexturePath() const;

private:
	const char* myTexture;
	CollisionEvent myOnCollisionEvent;
	UpdateEvent myUpdateEvent;
};


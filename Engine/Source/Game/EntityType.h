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
typedef std::function<void(CGameWorld*, Entity*, Entity*)> CollisionEvent;
typedef std::function<void(CGameWorld*, Entity*)> UpdateEvent;


class EntityType
{
public:
	EntityType() = default;
	EntityType(const char* aTexture, CollisionEvent anCollisionEvent);
	EntityType(const char* aTexture, CollisionEvent anCollisionEvent, UpdateEvent anUpdateEvent);
	EntityType(const char* aTexture, const char* aTag, CollisionEvent anCollisionEvent);
	EntityType(const char* aTexture, const char* aTag, CollisionEvent anCollisionEvent, UpdateEvent anUpdateEvent);
	CollisionEvent& OnCollisionEvent();
	UpdateEvent& OnUpdate();
	const char* GetTexturePath() const;
	const char* GetTag() const;

private:
	const char* myTag;
	const char* myTexture;
	CollisionEvent myOnCollisionEvent;
	UpdateEvent myUpdateEvent;

};


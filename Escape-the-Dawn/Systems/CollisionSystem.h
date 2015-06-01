#ifndef CollisionSystem_h__
#define CollisionSystem_h__

#include "System.h"
#include "logging.h"
#include <glew-1.10.0/include/GL/glew.h>

#include "Components/Transform.h"
#include "Components/Collision.h"
#include "Components/Bounds.h"
#include "Systems/TransformSystem.h"

namespace Systems
{

class CollisionSystem : public System
{
public:
	CollisionSystem(World* world) 
		: System(world) { }

	void UpdateEntity(double dt, EntityID entity, EntityID parent) override;
	void Intersects(EntityID, EntityID);
	void CreateBoundingBox(std::shared_ptr<Components::Bounds>);
};

}

#endif // CollisionSystem_h__

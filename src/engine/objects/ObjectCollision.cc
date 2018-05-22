#include"engine/objects/ObjectCollision.h"

ObjectCollision::ObjectCollision(const GameObject* object_1, const GameObject* object_2) :
	BasicObject(object_t::OBJECT_TO_OBJECT_COLLISION_TYPE),
	mObject_1(object_1),
	mObject_2(object_2)
{

}

ObjectCollision::~ObjectCollision()
{

}

std::pair<const GameObject*, const GameObject*> ObjectCollision::GetObjects() const
{
	return { mObject_1, mObject_2 };
}

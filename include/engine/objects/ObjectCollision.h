#ifndef OBJECT_COLLISION_HEADER_INCLUDED
#define OBJECT_COLLISION_HEADER_INCLUDED

#include"engine/util/Constants.h"
#include"engine/objects/BasicObject.h"

using namespace Constants::Types;
class GameObject;

class ObjectCollision :
	public BasicObject
{
public:
	ObjectCollision(const GameObject*, const GameObject*);
	~ObjectCollision();
	
	std::pair<const GameObject*, const GameObject*> GetObjects() const;

protected:
	const GameObject* mObject_1;
	const GameObject* mObject_2;

};


#endif
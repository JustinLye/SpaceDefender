#ifndef COLLIDER_HEADER_INCLUDED
#define COLLIDER_HEADER_INCLUDED
#ifdef COLLISION_DEBUG
#include<iostream>
#endif
#include<glm/glm.hpp>
#include"engine/shapes/CircleData.h"
#include"engine/objects/Transform.h"
/** @addtogroup EngineObjects */
/*@{*/
class Collider :
	public Transform
{
public:
	Collider();
	virtual ~Collider();
	virtual bool CollisionDetected(const Collider&) const;
	static bool CollisionDetected(const Transform&, const Transform&);
protected:
	float mRadius;

};

/*@}*/
#endif
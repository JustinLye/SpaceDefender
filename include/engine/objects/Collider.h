#ifndef COLLIDER_HEADER_INCLUDED
#define COLLIDER_HEADER_INCLUDED
#ifdef COLLISION_DEBUG
#include<iostream>
#endif
#include<glm/glm.hpp>
#include"engine/shapes/Circle.h"
#include"engine/objects/Transform.h"
class Collider :
	public Transform
{
public:
	Collider();
	virtual ~Collider();
	virtual bool CollisionDetected(const Collider&);
protected:
	float mRadius;

};
#endif
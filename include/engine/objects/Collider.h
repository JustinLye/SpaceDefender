/*
#ifndef COLLIDER_HEADER_INCLUDED
#define COLLIDER_HEADER_INCLUDED
#ifdef COLLISION_DEBUG
#include<iostream>
#endif
#include<glm/glm.hpp>
class Collider
{
public:
	Collider();
	virtual ~Collider();
	void Radius(const float&);
	const float& Radius() const;
	void Center(const glm::vec3&);
	const glm::vec3& Center() const;
	bool CollisionDetected(const Collider&);
	glm::vec3 mTranslate;
	glm::vec3 Position() const;
protected:
	float mRadius;
	glm::vec3 mCenter;
	glm::mat4 mIdentityMat;
	glm::mat4 mTranlateMat;
	
};



#endif
*/
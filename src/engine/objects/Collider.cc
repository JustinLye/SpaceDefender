#include"engine/objects/Collider.h"
Collider::Collider() :
	Transform()
{

}

Collider::~Collider()
{

}

bool Collider::CollisionDetected(const Collider& other) const
{
	float radius_sum = mTransformData.mScale.x + other.Scale().x;
	glm::vec3 diff = mTransformData.mPosition - other.Position();
	float dist = glm::length(diff);
	return dist < radius_sum;
}
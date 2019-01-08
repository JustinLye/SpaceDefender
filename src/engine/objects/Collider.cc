#include"engine/objects/Collider.h"
namespace sd_app {
namespace engine {
namespace objects {
namespace impl {
namespace collider {
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

bool Collider::CollisionDetected(const Transform& lhs, const Transform& rhs)
{
	float radius_sum = lhs.Scale().x + rhs.Scale().x;
	glm::vec3 diff = lhs.Position() - rhs.Position();
	float dist = glm::length(diff);
	return dist < radius_sum;
}
} // namespace collider
} // namespace impl
} // namespace objects
} // namespace engine
} // namespace sd_app
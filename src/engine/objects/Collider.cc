/*
#include"engine/objects/Collider.h"
Collider::Collider() :
	mRadius(0.0f),
	mCenter(glm::vec3(0.0f))
{

}

Collider::~Collider()
{

}

void Collider::Radius(const float& radius)
{
	mRadius = radius;
}

const float& Collider::Radius() const
{
	return mRadius;
}

void Collider::Center(const glm::vec3& center)
{
	mCenter = center;
}

glm::vec3 Collider::Position() const
{
	glm::vec4 pos;
	glm::mat4 translate_mat = glm::mat4(1.0f);
	translate_mat = glm::translate(mIdentityMat, mTranslate);
	pos = translate_mat * glm::vec4(mCenter.x, mCenter.y, mCenter.z, 1.0f);
	return glm::vec3(pos.x, pos.y, pos.z);
}

const glm::vec3& Collider::Center() const
{
	return mCenter;
}


bool Collider::CollisionDetected(const Collider& other)
{
	float radius_sum = mRadius + other.Radius();
	glm::vec3 this_pos = Position();
	glm::vec3 other_pos = other.Position();
	glm::vec3 dist = this_pos - other_pos;
	float dist_len = glm::length(dist);
#ifdef COLLISION_DEBUG
	bool result = dist_len <= radius_sum;
	if (result)
	{
		std::cout << "mRadius: " << mRadius;
		std::cout << "\tother.Radius(): " << other.Radius();
		std::cout << "\tmCenter: (" << this_pos.x << ',' << this_pos.y << ',' << this_pos.z << ')';
		std::cout << "\tother.Center(): (" << other_pos.x << ',' << other_pos.y << ',' << other_pos.z << ')';
		std::cout << "\tdist: (" << dist.x << ',' << dist.y << ',' << dist.z << ')';
		std::cout << "\tdist_len: " << dist_len << '\n';
	}
	return result;
#else
	return dist_len <= radius_sum;
#endif
}
*/
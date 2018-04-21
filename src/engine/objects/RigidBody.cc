#include"engine/objects/RigidBody.h"

RigidBody::RigidBody() :
	mVelocity(glm::vec3(0.0f)),
	mAcceleration(glm::vec3(0.0f)),
	mForce(glm::vec3(0.0f)),
	mMass(DFLT_MASS),
	mInverseMass(1.0f / DFLT_MASS),
	mDamping(DFLT_DAMPING)
{

}

RigidBody::~RigidBody()
{

}

void RigidBody::Update(const float& dt)
{
	// Update acceleration
	mAcceleration = mForce * mInverseMass;
	// Update velocity
	mVelocity = mVelocity * (std::powf(mDamping, dt)) + (mAcceleration * dt);
	mForce = glm::vec3(0.0f);
}

void RigidBody::Mass(const float& mass)
{
	mMass = mass;
	mInverseMass = (mass <= 0.0f) ? 0.0f : 1.0f / mass;
}

void RigidBody::Damping(const float& damping)
{
	mDamping = damping;
}

void RigidBody::Force(const glm::vec3& force)
{
	mForce = force;
}

const float& RigidBody::Mass() const
{
	return mMass;
}

const float& RigidBody::InverseMass() const
{
	return mInverseMass;
}

const float& RigidBody::Damping() const
{
	return mDamping;
}

const glm::vec3& RigidBody::Force() const
{
	return mForce;
}

const glm::vec3& RigidBody::Velocity() const
{
	return mVelocity;
}

const glm::vec3& RigidBody::Acceleration() const
{
	return mAcceleration;
}


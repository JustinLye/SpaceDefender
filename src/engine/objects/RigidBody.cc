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

void RigidBody::Update(float dt)
{
	// Update acceleration
	mAcceleration = mForce * mInverseMass;
	// Update velocity
	mVelocity = mVelocity * (std::powf(mDamping, dt)) + (mAcceleration * dt);
	mForce = glm::vec3(0.0f);
}

void RigidBody::Mass(float mass)
{
	mMass = mass;
	mInverseMass = (mass <= 0.0f) ? 0.0f : 1.0f / mass;
}

void RigidBody::Damping(float damping)
{
	mDamping = damping;
}

void RigidBody::Reset()
{
	mAcceleration = glm::vec3(0.0f);
	mVelocity = glm::vec3(0.0f);
	mForce = glm::vec3(0.0f);
}

void RigidBody::Force(const glm::vec3& force)
{
	mForce += force;
}

float RigidBody::Mass() const
{
	return mMass;
}

float RigidBody::InverseMass() const
{
	return mInverseMass;
}

float RigidBody::Damping() const
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


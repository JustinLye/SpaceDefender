
#include"game/Asteroid.h"

Asteroid::Asteroid() :
	GameObject(),
	mSpeed(0.0f),
	mHitPoints(2),
	mRotationSpeed(0.0f)
{

}

Asteroid::~Asteroid()
{

}

const Constants::Types::object_t& Asteroid::Type() const
{
	return Constants::Types::object_t::ASTEROID;
}

void Asteroid::Collide(const GameObject& object) const
{
	switch (object.Type())
	{
	case object_t::LASER:
		ReportCollision();
		if (mHitPoints <= 0)
		{
			Despawn();
		}
		break;
	case object_t::ASTEROID:
		ReportAsteroidCollision((const Asteroid&)object);
		break;
	}
}

void Asteroid::Despawn() const
{
	if (mColliderMap.size() > 0)
	{
		Notify(*this, event_t::TERMINATED_COLLIDABLE_OBJECT);
	}
	if (mHitPoints <= 0)
	{
		Notify(*this, event_t::PLAYER_DESTROYED_ASTEROID);
	}
	else
	{
		Notify(*this, event_t::OBJECT_OUT_OF_BOUNDS);
	}
}

void Asteroid::ReportAsteroidCollision(const Asteroid& asteroid) const
{
	AsteroidCollision collision(this->Id(), asteroid.Id());
	Notify(collision, event_t::ASTEROID_TO_ASTEROID_COLLISION);
}

const float& Asteroid::Speed() const
{
	return mSpeed;
}

const float& Asteroid::TerminateYPos() const
{
	return mTerminateYPos;
}

const float& Asteroid::RotationSpeed() const
{
	return mRotationSpeed;
}

const int& Asteroid::HitPoints() const
{
	return mHitPoints;
}

void Asteroid::Speed(const float& speed)
{
	mSpeed = speed;
}

void Asteroid::TerminateYPos(const float& ypos)
{
	mTerminateYPos = ypos;
}

void Asteroid::RotationSpeed(const float& speed)
{
	mRotationSpeed = speed;
}

void Asteroid::HitPoints(const int& points)
{
	mHitPoints = points;
}

void Asteroid::Update(const float& dt)
{
	if (mRigidBody != nullptr)
	{
		mRigidBody->Update(dt);
		if (std::abs(mRigidBody->Force().y) <= 0.0f)
		{
			mRigidBody->Force(glm::vec3(0.0f, -1 * mSpeed, 0.0f));
		}
		Translate(mRigidBody->Velocity());
	}
	else
	{
		Translate(glm::vec3(0.0f, mSpeed, 0.0f) * -dt);
	}
	Rotate(dt * mRotationSpeed, glm::vec3(0.0f, 0.0f, 1.0f));
	
}

bool Asteroid::Terminate() const
{
	return mTerminateYPos > mTransform.Position().y;
}
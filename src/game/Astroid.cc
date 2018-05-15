#include"game/Astroid.h"

Astroid::Astroid() :
	GameObject(),
	mSpeed(0.0f),
	mHitPoints(2)
{

}

Astroid::~Astroid()
{

}

const Constants::Types::object_t& Astroid::Type() const
{
	return Constants::Types::object_t::ASTROID;
}

void Astroid::Collide(const GameObject& object) const
{
	switch (object.Type())
	{
	case object_t::LASER:
		ReportCollision();
		std::cout << "hit points: " << mHitPoints << "\n";
		if (mHitPoints <= 0)
		{
			Despawn();
		}
		break;
	case object_t::ASTROID:
		ReportAstroidCollision((const Astroid&)object);
		break;
	}
}

void Astroid::Despawn() const
{
	if (mColliderMap.size() > 0)
	{
		Notify(*this, event_t::TERMINATED_COLLIDABLE_OBJECT);
	}
	if (mHitPoints <= 0)
	{
		Notify(*this, event_t::PLAYER_DESTROYED_ASTROID);
	}
}

void Astroid::ReportAstroidCollision(const Astroid& astroid) const
{
	AstroidCollision collision(this->Id(), astroid.Id());
	Notify(collision, event_t::ASTROID_TO_ASTROID_COLLISION);
}

const float& Astroid::Speed() const
{
	return mSpeed;
}

const float& Astroid::TerminateYPos() const
{
	return mTerminateYPos;
}

const int& Astroid::HitPoints() const
{
	return mHitPoints;
}

void Astroid::Speed(const float& speed)
{
	mSpeed = speed;
}

void Astroid::TerminateYPos(const float& ypos)
{
	mTerminateYPos = ypos;
}

void Astroid::HitPoints(const int& points)
{
	mHitPoints = points;
}

void Astroid::Update(const float& dt)
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
	Rotate(-dt, glm::vec3(0.0f, 0.0f, 1.0f));
	
}

bool Astroid::Terminate() const
{
	return mTerminateYPos > mTransform.Position().y;
}
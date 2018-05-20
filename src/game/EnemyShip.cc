#include"game/EnemyShip.h"

EnemyShip::EnemyShip() :
	GameObject(),
	mSpeed(0.0f),
	mHitPoints(1),
	mTerminateYPos(0.0f),
	mType(ENEMY_SHIP)
{

}

EnemyShip::~EnemyShip()
{

}

const object_t& EnemyShip::Type() const
{
	return mType;
}

void EnemyShip::Update(const float& dt)
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
}

bool EnemyShip::Terminate() const
{
	return mTransform.Position().y < mTerminateYPos;
}

void EnemyShip::Despawn() const
{
	if (mHitPoints <= 0)
	{
		Notify(*this, event_t::PLAYER_DESTROYED_ENEMY_SHIP);
	}
	else
	{
		Notify(*this, event_t::TERMINATED_COLLIDABLE_OBJECT);
	}
}

const float& EnemyShip::Speed() const
{
	return mSpeed;
}

const int& EnemyShip::HitPoints() const
{
	return mHitPoints;
}

const float& EnemyShip::TerminateYPos() const
{
	return mTerminateYPos;
}


void EnemyShip::Speed(const float& speed)
{
	mSpeed = speed;
}

void EnemyShip::HitPoints(const int& hp)
{
	mHitPoints = hp;
}

void EnemyShip::TerminateYPos(const float& pos)
{
	mTerminateYPos = pos;
}
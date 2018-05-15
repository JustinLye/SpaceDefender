#include"game/Player.h"

Player::Player() :
	GameObject(),
	mSpeed(3.0f),
	mStep(200.0f),
	mTargetXPos(OpenGLUtility::GetScreenWidth() /2.0f),
	mSpeedBoost(1.0f),
	mMaxBoost(2.0f),
	mLaserCannon(nullptr)
{

}

Player::~Player()
{
}

const Constants::Types::object_t& Player::Type() const
{
	return Constants::Types::object_t::PLAYER;
}

void Player::Render(const glm::mat4& proj_mat, const glm::mat4& view_mat)
{
#ifdef ENGINE_DEBUG
	if (!mRenderer)
	{
		return;
	}
#else
	assert(mRenderer != nullptr);
#endif
	RenderDrawableObjects(proj_mat, view_mat);
	RenderGameObjects(proj_mat, view_mat);
	if (mLaserCannon)
	{
		mLaserCannon->Render(proj_mat, view_mat);
	}
}

void Player::Update(const float& dt)
{
/*	float distance = mTargetXPos - mTransform.Position().x;
	float delta_x = distance*dt*mSpeed*mSpeedBoost;
	if (std::abs(distance) > 0.01f)
	{
		Translate(glm::vec3(delta_x, 0.0f, 0.0f));
	}*/
	static int i = 61;
	if (mRigidBody != nullptr)
	{
		mRigidBody->Update(dt);
		if (i > 60)
		{
			i = 0;
			std::cout << "Velocity: " << mRigidBody->Velocity().x << " InverseMass: " << mRigidBody->InverseMass() << '\n';
		}
		else
		{
			++i;
		}
		
		Translate(mRigidBody->Velocity());
	}
	
	if (mLaserCannon)
	{
		mLaserCannon->Update(dt*mLaserCannon->ProjectileSpeed());
	}
}

void Player::DoDetection(Collider* collider)
{
	if (CollisionDetected(collider))
	{
		// play collided with something
	}
	mLaserCannon->DoDetection(collider);
}

void Player::HandleKeyboardInput(GLFWwindow* window)
{
}

void Player::AttachCannon(LaserCannon* cannon)
{
	mLaserCannon = cannon;
	mLaserCannon->AttachTo(*this);
}

void Player::Strafe(const Constants::Types::DIRECTION& dir)
{
	if (dir == Constants::Types::DIRECTION::LEFT)
	{
		mRigidBody->Force(glm::vec3(-10.0f, 0.0f, 0.0f));
	//	mTargetXPos = mTransform.Position().x - mStep;
	}
	if (dir == Constants::Types::DIRECTION::RIGHT)
	{
		mRigidBody->Force(glm::vec3(10.0f, 0.0f, 0.0f));
	}
}

void Player::FireCannon()
{
	if (mLaserCannon)
	{
		unsigned int result = mLaserCannon->Fire();
		if (result != LaserCannon::NOT_INDEX)
		{
			std::cout << "cannon fired\n";
		}
	}
}

void Player::CustomScaleActions(const float& scale)
{
	if (mLaserCannon)
	{
		mLaserCannon->Scale(scale);
	}
}

void Player::CustomTranslateActions(const glm::vec3& translation)
{
	if (mLaserCannon)
	{
		mLaserCannon->Translate(translation);
	}
}

void Player::Speed(const float& speed)
{
	mSpeed = speed;
}

const float& Player::Speed() const
{
	return mSpeed;
}

void Player::Boost(const float& boost)
{
	mSpeedBoost = boost;
}

const float& Player::Boost() const
{
	return mSpeedBoost;
}

const float& Player::CurrentGunTemp() const
{
#ifdef ENGINE_DEBUG
	assert(mLaserCannon != nullptr);
#endif
	return mLaserCannon->CurrentGunTemp();
}

const float& Player::MaxGunTemp() const
{
#ifdef ENGINE_DEBUG
	assert(mLaserCannon != nullptr);
#endif
	return mLaserCannon->MaxGunTemp();
}

bool Player::GunOverHeated() const
{
#ifdef ENGINE_DEBUG
	assert(mLaserCannon != nullptr);
#endif
	return mLaserCannon->GunOverHeated();
}

void Player::AddObserver(Observer* observer)
{
	if (!ObserverIsMapped(observer))
	{
		mObserverMap.insert({ observer->Id(), observer });
	}
	if (mLaserCannon)
	{
		mLaserCannon->AddObserver(observer);
	}
}

void Player::RemoveObserver(Observer* observer)
{
	mObserverMap.erase(observer->Id());
	mLaserCannon->RemoveObserver(observer);
}
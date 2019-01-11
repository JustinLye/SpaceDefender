#include"game/Player.h"
namespace sd_app {
namespace game {
namespace impl {
namespace player {
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

object_t Player::Type() const
{
	return object_t::PLAYER;
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

void Player::Update(float dt)
{
/*	float distance = mTargetXPos - mTransform.Position().x;
	float delta_x = distance*dt*mSpeed*mSpeedBoost;
	if (std::abs(distance) > 0.01f)
	{
		Translate(glm::vec3(delta_x, 0.0f, 0.0f));
	}*/
	if (mRigidBody != nullptr)
	{
		mRigidBody->Update(dt);
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

void Player::Strafe(const direction_t& dir)
{
	if (dir == direction_t::LEFT)
	{
		mRigidBody->Force(glm::vec3(-10.0f, 0.0f, 0.0f));
	//	mTargetXPos = mTransform.Position().x - mStep;
	}
	if (dir == direction_t::RIGHT)
	{
		mRigidBody->Force(glm::vec3(10.0f, 0.0f, 0.0f));
	}
}

void Player::FireCannon()
{
	if (mLaserCannon)
	{
		unsigned int result = mLaserCannon->Fire();
	}
}

void Player::CustomScaleActions(float scale)
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

void Player::Speed(float speed)
{
	mSpeed = speed;
}

float Player::Speed() const
{
	return mSpeed;
}

void Player::Boost(float boost)
{
	mSpeedBoost = boost;
}

float Player::Boost() const
{
	return mSpeedBoost;
}

float Player::CurrentGunTemp() const
{
#ifdef ENGINE_DEBUG
	assert(mLaserCannon != nullptr);
#endif
	return mLaserCannon->CurrentGunTemp();
}

float Player::MaxGunTemp() const
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

void Player::AddObserver(Observer<GameObject>* observer)
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

void Player::RemoveObserver(Observer<GameObject>* observer)
{
	mObserverMap.erase(observer->Id());
	mLaserCannon->RemoveObserver(observer);
}
} // namespace player
} // namespace impl
} // namespace game
} // namespace sd_app
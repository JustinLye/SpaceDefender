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
	RenderShapes(proj_mat, view_mat);
	RenderGameObjects(proj_mat, view_mat);
	if (mLaserCannon)
	{
		mLaserCannon->Render(proj_mat, view_mat);
	}
}

void Player::Update(const float& dt)
{
	float distance = mTargetXPos - mTransform.Position().x;
	if (mSpeedBoost > 1.0f)
	{
		mSpeedBoost *= 0.95f;
		if (mSpeedBoost < 1.0f)
		{
			mSpeedBoost = 1.0f;
		}
	}
	float delta_x = distance*dt*mSpeed*mSpeedBoost;
	if (std::abs(distance) > 0.01f)
	{
	
		//float delta_x = distance*dt;
		Translate(glm::vec3(delta_x, 0.0f, 0.0f));
		if (mLaserCannon)
		{
			mLaserCannon->GetTransform().Translate(glm::vec3(delta_x, 0.0f, 0.0f));
		}
	}
	if (mLaserCannon)
	{

		mLaserCannon->Update(dt*mLaserCannon->ProjectileSpeed());
	}
}

void Player::HandleKeyboardInput(GLFWwindow* window)
{
}

void Player::AttachCannon(LaserCannon* cannon)
{
	mLaserCannon = cannon;
	mLaserCannon->AttachTo(*this);
	mLaserCannon->GetTransform().Translate(glm::vec3(0.0f, 100.0f, 0.0f));
}

void Player::Strafe(const Constants::Movement::DIRECTION& dir)
{
	if (dir == Constants::Movement::DIRECTION::LEFT)
	{
		mTargetXPos = mTransform.Position().x - mStep;
	}
	if (dir == Constants::Movement::DIRECTION::RIGHT)
	{
		mTargetXPos = mTransform.Position().x + mStep;
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

void Player::Speed(const float& speed)
{
	mSpeed = speed;
}

const float& Player::Speed() const
{
	return mSpeed;
}

void Player::Boost()
{
	mSpeedBoost = mMaxBoost;
}
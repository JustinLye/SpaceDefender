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
	case Constants::Types::object_t::LASER:
		ReportCollision();
		std::cout << "hit points: " << mHitPoints << "\n";
		if (mHitPoints <= 0)
		{
			Despawn();
		}
		break;
	}
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
	Translate(glm::vec3(0.0f, mSpeed, 0.0f) * -dt);
}

bool Astroid::Terminate() const
{
	return mTerminateYPos > mTransform.Position().y;
}
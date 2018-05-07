#include"game/Explosion.h"

Explosion::Explosion() :
	GameObject(),
	mSpeed(0.0f),
	mMaxScale(0.0f)
{

}

Explosion::~Explosion()
{

}

const object_t& Explosion::Type() const
{
	return object_t::EXPLOSION_OBJECT;
}

void Explosion::Update(const float& dt)
{

	Scale(1.0f + (mSpeed * dt));
}

bool Explosion::Terminate() const
{
	return mMaxScale <= Scale().x;
}

void Explosion::Speed(const float& speed)
{
	mSpeed = speed;
}

void Explosion::MaxScale(const float& max_scale)
{
	mMaxScale = max_scale;
}

const float& Explosion::Speed() const
{
	return mSpeed;
}

const float& Explosion::MaxScale() const
{
	return mMaxScale;
}
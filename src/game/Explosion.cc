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

object_t Explosion::Type() const
{
	return object_t::EXPLOSION_OBJECT;
}

void Explosion::Update(float dt)
{

	Scale(1.0f + (mSpeed * dt));
}

bool Explosion::Terminate() const
{
	return mMaxScale <= Scale().x;
}

void Explosion::Speed(float speed)
{
	mSpeed = speed;
}

void Explosion::MaxScale(float max_scale)
{
	mMaxScale = max_scale;
}

float Explosion::Speed() const
{
	return mSpeed;
}

float Explosion::MaxScale() const
{
	return mMaxScale;
}
#include"game/Explosion.h"
namespace sd_app {
namespace game {
namespace impl {
namespace explosion {
Explosion::Explosion() :
	GameObject(),
	mSpeed(0.0),
	mMaxScale(0.0)
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

void Explosion::Speed(double speed)
{
	mSpeed = speed;
}

void Explosion::MaxScale(double max_scale)
{
	mMaxScale = max_scale;
}

double Explosion::Speed() const
{
	return mSpeed;
}

double Explosion::MaxScale() const
{
	return mMaxScale;
}
} // namespace explosion
} // namespace impl
} // namespace game
} // namespace sd_app

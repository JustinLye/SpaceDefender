#include"game/AsteroidCollision.h"
namespace sd_app {
namespace game {
namespace impl {
namespace asteroid_collision {
AsteroidCollision::AsteroidCollision(const unsigned int& asteroid_1, const unsigned int& asteroid_2) :
	GameObject(),
	mAsteroid_1(asteroid_1),
	mAsteroid_2(asteroid_2)
{

}

AsteroidCollision::~AsteroidCollision()
{

}

object_t AsteroidCollision::Type() const
{
	return object_t::ASTEROID_COLLISION;
}

std::pair<const unsigned int&, const unsigned int&> AsteroidCollision::GetAsteroidIds() const
{
	return std::pair<const unsigned int&, const unsigned int&>(mAsteroid_1, mAsteroid_2);
}
} // namespace asteroid_collision
} // namespace impl
using AsteroidCollision = impl::asteroid_collision::AsteroidCollision;
} // namespace game
} // namespace sd_app
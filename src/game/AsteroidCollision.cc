#include"game/AsteroidCollision.h"

AsteroidCollision::AsteroidCollision(const unsigned int& asteroid_1, const unsigned int& asteroid_2) :
	GameObject(),
	mAsteroid_1(asteroid_1),
	mAsteroid_2(asteroid_2)
{

}

AsteroidCollision::~AsteroidCollision()
{

}

std::pair<const unsigned int&, const unsigned int&> AsteroidCollision::GetAsteroidIds() const
{
	return std::pair<const unsigned int&, const unsigned int&>(mAsteroid_1, mAsteroid_2);
}
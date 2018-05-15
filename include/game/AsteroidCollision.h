#ifndef ASTEROID_COLLISION_HEADER_INCLUDED
#define ASTEROID_COLLISION_HEADER_INCLUDED

#include"engine/objects/GameObject.h"
#include"game/Asteroid.h"

class AsteroidCollision : 
	public GameObject
{
public:
	AsteroidCollision(const unsigned int&, const unsigned int&);
	~AsteroidCollision();
	std::pair<const unsigned int&, const unsigned int&> GetAsteroidIds() const;
protected:
	unsigned int mAsteroid_1;
	unsigned int mAsteroid_2;
};

#endif
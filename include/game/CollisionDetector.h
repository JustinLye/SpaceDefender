#ifndef COLLISION_DETECTOR_HEADER_INCLUDED
#define COLLISION_DETECTOR_HEADER_INCLUDED
#include"engine/util/Constants.h"
#include"engine/objects/Observer.h"
#include"engine/objects/Subject.h"
#include"engine/objects/GameObject.h"
#include"game/Asteroid.h"
#include"game/Laser.h"
#include"game/EnemyShip.h"

#ifdef ENGINE_DEBUG
#include"engine/util/DebugFunctions.h"
#endif

using namespace Constants::Types;

class CollisionDetector :
	public Subject,
	public Observer
{
public:
	CollisionDetector();
	~CollisionDetector();
	void DoDetection(const float&);
	void OnNotify(const GameObject&, const Constants::Types::event_t&);
protected:
	std::map<unsigned int, const Asteroid*> mAsteroidMap;
	std::map<unsigned int, const Laser*> mLaserMap;
	std::map<unsigned int, const EnemyShip*> mEnemyShipMap;

};
#endif
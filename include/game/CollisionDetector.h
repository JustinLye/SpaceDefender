#ifndef COLLISION_DETECTOR_HEADER_INCLUDED
#define COLLISION_DETECTOR_HEADER_INCLUDED
#include"engine/util/Constants.h"
#include"engine/objects/Observer.h"
#include"engine/objects/Subject.h"
#include"engine/objects/GameObject.h"
#include"game/Astroid.h"
#include"game/Laser.h"
class CollisionDetector :
	public Subject,
	public Observer
{
public:
	CollisionDetector();
	~CollisionDetector();
	void DoDetection();
	void OnNotify(const GameObject&, const Constants::Types::event_t&);
protected:
	std::map<unsigned int, const Astroid*> mAstroidMap;
	std::map<unsigned int, const Laser*> mLaserMap;

};
#endif
#ifndef COLLISION_DETECTOR_HEADER_INCLUDED
#define COLLISION_DETECTOR_HEADER_INCLUDED
#include"engine/util/Constants.h"
#include"engine/objects/Observer.h"
#include"engine/objects/Subject.h"
#include"engine/objects/GameObject.h"
#include"game/Astroid.h"
class CollisionDetector :
	public Subject,
	public Observer
{
public:
	CollisionDetector();
	~CollisionDetector();
	void DoDetection(GameObject*);
	void OnNotify(const GameObject&, const Constants::event_t&);
protected:
	std::map<unsigned int, Astroid*> mAstroidMap;


};
#endif
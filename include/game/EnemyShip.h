#ifndef ENEMY_SHIP_HEADER_INCLUDED
#define ENEMY_SHIP_HEADER_INCLUDED
#include<limits>
#include<algorithm>
#include<boost/lexical_cast.hpp>
#ifdef ENEMY_SHIP_DEBUG
#include"engine/util/DebugFunctions.h"
#endif

#include"engine/objects/GameObject.h"
#include"engine/util/DistanceEntry.h"
#include"engine/util/Logger.h"
#include"game/ActiveObjectTracker.h"

using namespace Constants::Types;
/** @addtogroup GameActors */
/*@{*/
class EnemyShip :
	public GameObject
{
public:
	typedef unsigned int size_t;
	typedef int index_t;

	EnemyShip();
	EnemyShip(const EnemyShip&);
	~EnemyShip();

	object_t Type() const override;
	void Update(const float&) override;
	void Collide(const GameObject&) const override;

	bool Terminate() const;
	void Despawn() const;

	const float& Speed() const;
	const int& HitPoints() const;
	const float& TerminateYPos() const;
	const glm::vec3& Up() const;

	void Speed(const float&);
	void HitPoints(const int&);
	void TerminateYPos(const float&);
	void Up(const glm::vec3&);

	void AddActiveObjectTracker(const ActiveObjectTracker*);

protected:
	float mSpeed;
	int mHitPoints;
	float mTerminateYPos;
	const ActiveObjectTracker* mTracker;
	glm::vec3 mFront;
	Logger* mLogger;
	std::vector<const GameObject*> mCloseObjects;
	glm::vec3 mUp;
	void ProximityScan(); //< Fills mCloseObjects w/ GameObjects in the surrounding area.
};
/*@}*/
#endif
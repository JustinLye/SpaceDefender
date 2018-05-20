#ifndef ENEMY_SHIP_HEADER_INCLUDED
#define ENEMY_SHIP_HEADER_INCLUDED
#ifdef ENEMY_SHIP_DEBUG
#include"engine/util/DebugFunctions.h"
#endif
#include"engine/objects/GameObject.h"

using namespace Constants::Types;

class EnemyShip :
	public GameObject
{
public:
	EnemyShip();
	~EnemyShip();

	const object_t& Type() const override;
	void Update(const float&) override;

	bool Terminate() const;
	void Despawn() const;

	const float& Speed() const;
	const int& HitPoints() const;
	const float& TerminateYPos() const;

	void Speed(const float&);
	void HitPoints(const int&);
	void TerminateYPos(const float&);

protected:
	float mSpeed;
	int mHitPoints;
	float mTerminateYPos;
	object_t mType;
	

};

#endif
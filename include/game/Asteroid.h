#ifndef ASTEROID_HEADER_INCLUDED
#define ASTEROID_HEADER_INCLUDED

#include"engine/objects/GameObject.h"
#include"game/AsteroidCollision.h"
#include"game/ActiveObjectTracker.h"

using namespace Constants::Types;
class Asteroid :
	public GameObject
{
public:
	Asteroid();
	Asteroid(const Asteroid&);
	~Asteroid();
	
	object_t Type() const override;
	void Collide(const GameObject&) const override;
	const float& Speed() const;
	const float& TerminateYPos() const;
	const float& RotationSpeed() const;

	void Speed(const float&);
	void TerminateYPos(const float&);
	void RotationSpeed(const float&);

	void Update(const float&) override;
	
	bool Terminate() const;
	void HitPoints(const int&);
	const int& HitPoints() const;
	void ReportAsteroidCollision(const Asteroid&) const;
	void AddActiveObjectTracker(const ActiveObjectTracker*);
	void Despawn() const override;

protected:
	float mSpeed;
	int mHitPoints;
	float mTerminateYPos;
	float mRotationSpeed;
	const ActiveObjectTracker* mTracker;
};

#endif
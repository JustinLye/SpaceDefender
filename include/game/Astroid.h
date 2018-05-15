#ifndef ASTROID_HEADER_INCLUDED
#define ASTROID_HEADER_INCLUDED

#include"engine/objects/GameObject.h"
#include"game/AstroidCollision.h"
using namespace Constants::Types;
class Astroid :
	public GameObject
{
public:
	Astroid();
	~Astroid();
	
	const object_t& Type() const override;
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
	void ReportAstroidCollision(const Astroid&) const;

	void Despawn() const override;

protected:
	float mSpeed;
	int mHitPoints;
	float mTerminateYPos;
	float mRotationSpeed;
};

#endif
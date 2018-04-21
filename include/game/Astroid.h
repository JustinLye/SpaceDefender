#ifndef ASTROID_HEADER_INCLUDED
#define ASTROID_HEADER_INCLUDED

#include"engine/objects/GameObject.h"

class Astroid :
	public GameObject
{
public:
	Astroid();
	~Astroid();
	
	const Constants::Types::object_t& Type() const override;
	void Collide(const GameObject&) const override;
	const float& Speed() const;
	const float& TerminateYPos() const;

	void Speed(const float&);
	void TerminateYPos(const float&);

	void Update(const float&) override;
	
	bool Terminate() const;
	void HitPoints(const int&);
	const int& HitPoints() const;
protected:
	float mSpeed;
	int mHitPoints;
	float mTerminateYPos;
};

#endif
#ifndef LASER_HEADER_INCLUDED
#define LASER_HEADER_INCLUDED
#ifdef ENGINE_DEBUG
#include"engine/util/DebugFunctions.h"
#endif
#include"engine/objects/GameObject.h"


class Laser :
	public GameObject
{
public:
	Laser();
	~Laser();
	const Constants::Types::object_t& Type() const override;
	void Collide(const GameObject&) const override;
	void Update(const float&) override;
	void Render(const glm::mat4&, const glm::mat4&) override;
	void TerminateYPos(const float&);
	const float& TerminateYPos() const;
	bool Terminate() const;

protected:
	float mTerminateYPos;
	int mAttackDamage;
};

#endif
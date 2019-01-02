
#ifndef RIGID_BODY_HEADER_INCLUDED
#define RIGID_BODY_HEADER_INCLUDED
#include"engine/util/Constants.h"

using namespace Constants::Physics;

/** @addtogroup EngineObjects */
/*@{*/

class RigidBody
{
public:
	RigidBody();
	virtual ~RigidBody();
	void Update(const float&);

	void Mass(const float&);
	void Damping(const float&);
	void Force(const glm::vec3&);
	void Reset();


	const float& Mass() const;
	const float& InverseMass() const;
	const float& Damping() const;
	const glm::vec3& Force() const;
	const glm::vec3& Velocity() const;
	const glm::vec3& Acceleration() const;

protected:
	float mMass;
	float mInverseMass;
	float mDamping;
	glm::vec3 mForce;
	glm::vec3 mVelocity;
	glm::vec3 mAcceleration;
};

/*@}*/

#endif

#ifndef RIGID_BODY_HEADER_INCLUDED
#define RIGID_BODY_HEADER_INCLUDED
#include"engine/util/Constants.h"
namespace sd_app {
namespace engine {
namespace objects {
namespace impl {
namespace rigid_body {
using namespace constants::physics;

/** @addtogroup EngineObjects */
/*@{*/

class RigidBody
{
public:
	RigidBody();
	virtual ~RigidBody();
	void Update(float);

	void Mass(float);
	void Damping(float);
	void Force(const glm::vec3&);
	void Reset();


	float Mass() const;
	float InverseMass() const;
	float Damping() const;
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
} // namespace renderable_object
} // namespace impl
using RigidBody = impl::rigid_body::RigidBody;
} // namespace objects
} // namespace engine
} // namespace sd_app
#endif
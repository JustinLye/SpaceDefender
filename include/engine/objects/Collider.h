#ifndef COLLIDER_HEADER_INCLUDED
#define COLLIDER_HEADER_INCLUDED
#ifdef COLLISION_DEBUG
#include<iostream>
#endif
#include<glm/glm.hpp>
#include"engine/shapes/CircleData.h"
#include"engine/objects/Transform.h"

namespace sd_app {
namespace engine {
namespace objects {
namespace impl {
namespace collider {
/** @addtogroup EngineObjects */
/*@{*/
class Collider :
  public Transform {
public:
  Collider();
  virtual ~Collider();
  virtual bool CollisionDetected(const Collider&) const;
  static bool CollisionDetected(const Transform&, const Transform&);
protected:
  float mRadius;

};

/*@}*/
} // namespace collider
} // namespace impl
using Collider = impl::collider::Collider;
} // namespace objects
} // namespace engine
} // namespace sd_app


#endif
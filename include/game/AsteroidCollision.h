#ifndef ASTEROID_COLLISION_HEADER_INCLUDED
#define ASTEROID_COLLISION_HEADER_INCLUDED

#include"engine/objects/GameObject.h"
#include"game/Asteroid.h"


namespace sd_app {
namespace game {
namespace impl {
namespace asteroid_collision {
using object_t = engine::constants::types::object_t;
using GameObject = engine::objects::GameObject;

/** @addtogroup GameWorld */
/*@{*/
class AsteroidCollision :
  public GameObject {
public:
  AsteroidCollision(const unsigned int&, const unsigned int&);
  ~AsteroidCollision();

  object_t Type() const override;
  std::pair<const unsigned int&, const unsigned int&> GetAsteroidIds() const;
protected:
  unsigned int mAsteroid_1;
  unsigned int mAsteroid_2;
};
/*@}*/
} // namespace asteroid_collision
} // namespace impl
using AsteroidCollision = impl::asteroid_collision::AsteroidCollision;
} // namespace game
} // namespace sd_app


#endif
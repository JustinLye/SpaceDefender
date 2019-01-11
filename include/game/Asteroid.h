#ifndef ASTEROID_HEADER_INCLUDED
#define ASTEROID_HEADER_INCLUDED

#include"engine/objects/GameObject.h"
#include"game/AsteroidCollision.h"
#include"game/ActiveObjectTracker.h"

namespace sd_app {
namespace game {
namespace impl {
namespace asteroid {

using event_t = engine::constants::types::event_t;
using object_t = engine::constants::types::object_t;
using GameObject = engine::objects::GameObject;

/** @addtogroup GameActors */
/*@{*/
class Asteroid :
  public GameObject {
public:
  Asteroid();
  Asteroid(const Asteroid&);
  ~Asteroid();

  object_t Type() const override;
  void Collide(const GameObject&) const override;
  float Speed() const;
  float TerminateYPos() const;
  float RotationSpeed() const;

  void Speed(float);
  void TerminateYPos(float);
  void RotationSpeed(float);

  void Update(float) override;

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
/*@}*/
} // namespace asteroid
} // namespace impl
using Asteroid = impl::asteroid::Asteroid;
} // namespace game
} // namespace sd_app


#endif
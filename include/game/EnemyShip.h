#ifndef ENEMY_SHIP_HEADER_INCLUDED
#define ENEMY_SHIP_HEADER_INCLUDED
#include<limits>
#include<algorithm>
#ifdef ENEMY_SHIP_DEBUG
#include"engine/util/DebugFunctions.h"
#endif

#include"engine/objects/GameObject.h"
#include"engine/util/DistanceEntry.h"
#include"engine/util/Logger.h"
#include"game/ActiveObjectTracker.h"

namespace sd_app {
namespace game {
namespace impl {
namespace enemy_ship {
using event_t = engine::constants::types::event_t;
using object_t = engine::constants::types::object_t;
using GameObject = engine::objects::GameObject;
using Transform = engine::objects::Transform;
using DistanceEntry = engine::util::DistanceEntry;
using engine::util::TypeToString;
using engine::util::VecToVecAngle;
using Logger = engine::util::Logger;

/** @addtogroup GameActors */
/*@{*/
class EnemyShip :
  public GameObject {
public:
  typedef unsigned int size_t;
  typedef int index_t;

  EnemyShip();
  EnemyShip(const EnemyShip&);
  ~EnemyShip();

  object_t Type() const override;
  void Update(float) override;
  void Collide(const GameObject&) const override;

  bool Terminate() const;
  void Despawn() const;

  double Speed() const;
  const int& HitPoints() const;
  float TerminateYPos() const;
  const glm::vec3& Up() const;

  void Speed(double);
  void HitPoints(const int&);
  void TerminateYPos(float);
  void Up(const glm::vec3&);

  void AddActiveObjectTracker(const ActiveObjectTracker*);

protected:
  double mSpeed;
  int mHitPoints;
  float mTerminateYPos;
  const ActiveObjectTracker* mTracker;
  glm::vec3 mFront;
  Logger* mLogger;
  std::vector<const GameObject*> mCloseObjects;
  glm::vec3 mUp;
  void ProximityScan(); //< Fills mCloseObjects w/ GameObjects in the surrounding area.
};
/*@}*/
} // namespace enemy_ship
} // namespace impl
using EnemyShip = impl::enemy_ship::EnemyShip;
} // namespace game
} // namespace sd_app
#endif
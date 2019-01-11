#ifndef COLLISION_DETECTOR_HEADER_INCLUDED
#define COLLISION_DETECTOR_HEADER_INCLUDED
#include"engine/util/Constants.h"
#include"core/Observer.h"
#include"core/Subject.h"
#include"engine/objects/GameObject.h"
#include"game/Asteroid.h"
#include"game/Laser.h"
#include"game/EnemyShip.h"

#ifdef ENGINE_DEBUG
#include"engine/util/DebugFunctions.h"
#endif

namespace sd_app {
namespace game {
namespace impl {
namespace collision_detector {
using event_t = engine::constants::types::event_t;
using object_t = engine::constants::types::object_t;
template<class T>
using Subject = core::Subject<T>;
template<class T>
using Observer = core::Observer<T>;
using GameObject = engine::objects::GameObject;

/** @addtogroup GameWorld */
/*@{*/
class CollisionDetector :
  public Subject<GameObject>,
  public Observer<GameObject> {
public:
  CollisionDetector();
  ~CollisionDetector();
  void DoDetection(float);
  virtual void OnNotify(const GameObject&, const event_t&) override;
protected:
  std::map<unsigned int, const Asteroid*> mAsteroidMap;
  std::map<unsigned int, const Laser*> mLaserMap;
  std::map<unsigned int, const EnemyShip*> mEnemyShipMap;
};
/*@}*/
} // namespace collision_detector
} // namespace impl
using CollisionDetector = impl::collision_detector::CollisionDetector;
} // namespace game
} // namespace sd_app
#endif
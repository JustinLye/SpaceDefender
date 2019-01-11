#ifndef LASER_CANNON_HEADER_INCLUDED
#define LASER_CANNON_HEADER_INCLUDED
#ifdef LASER_CANNON_DEBUG
#include"engine/util/DebugFunctions.h"
#endif // LASER_CANNON_DEBUG

#include<chrono>
#include"core/Observer.h"
#include"core/Subject.h"
#include"engine/objects/TexRenderer.h"
#include"engine/containers/ObjectManager.h"
#include"game/Laser.h"

#ifdef COLLISION_DEBUG
#include"engine/shapes/CircleData.h"
#endif

namespace sd_app {
namespace game {
namespace impl {
namespace laser_cannon {
using event_t = engine::constants::types::event_t;
using object_t = engine::constants::types::object_t;

template<class T>
using Subject = core::Subject<T>;
template<class T>
using Observer = core::Observer<T>;

template<class T>
using ObjectManager = engine::containers::ObjectManager<T>;

using DrawableObject = engine::objects::DrawableObject;
using GameObject = engine::objects::GameObject;
using Collider = engine::objects::Collider;
using Transform = engine::objects::Transform;
using Renderer = engine::objects::Renderer;
using TexRenderer = engine::objects::TexRenderer;

using ShaderProgram = engine::util::ShaderProgram;

/** @addtogroup GameComponents */
/*@{*/
class LaserCannon :
  public Subject<GameObject>,
  public Observer<GameObject>,
  public ObjectManager<Laser> {
public:
  LaserCannon(DrawableObject*, ShaderProgram*);
  ~LaserCannon();
  int MaxCapacity();
  int MaxActiveCapacity();
  virtual void OnNotify(const GameObject&, const event_t&) override;
  void AddObserver(Observer*) override;
  void RemoveObserver(Observer*) override;

  void DoDetection(Collider*);

  float ProjectileSpeed() const;
  float CooldownTime() const;
  float LaserTermYPos() const;
  float OverheatCooldownTime() const;
  float CurrentGunTemp() const;
  float MaxGunTemp() const;
  bool GunOverHeated() const;

  const Transform& GetTransform() const;
  Transform& GetTransform();
  void Scale(float);
  void ScaleLasers(const glm::vec3&);
  void Translate(const glm::vec3&);
  unsigned int Fire();
  void ProjectileSpeed(float);
  void CooldownTime(float);
  void LaserTermYPos(float);
  void OverheatCooldownTime(float);
  bool DestructionPred(Laser*) const override;
  void AttachTo(const GameObject&);
  void Render(const glm::mat4&, const glm::mat4&) override;
  bool operator<(const LaserCannon&) const;

protected:
  Transform mTransform;
  DrawableObject* mShape;
  ShaderProgram* mShaderProg;
  Renderer* mRenderer;
  Collider* mCollider;
  Laser* ConstructObject();
  float mProjectileSpeed;
  std::chrono::time_point<std::chrono::steady_clock> mLastShotTime;
  float mCooldownTime;
  float mLaserTermYPos;
  float mOverheatCooldownTime;
  float mMaxGunTemp;
  float mCoolDownTemp;
  float mShotTemp;
  float mCoolDownStepTemp;
  float mCurrentGunTemp;
  bool mGunOverHeated;

  void CustomAllocOps(unsigned int) override;
  void CustomDeallocOps(unsigned int) override;
  void CustomInitOps() override;
  void CustomUpdateOps(float);
};
/*@}*/
} // namespace laser_cannon
} // namespace impl
using LaserCannon = impl::laser_cannon::LaserCannon;
} // namespace game
} // namespace sd_app


#endif
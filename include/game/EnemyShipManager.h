#ifndef ENEMY_SHIP_MANAGER_HEADER_INCLUDED
#define ENEMY_SHIP_MANAGER_HEADER_INCLUDED

#include<random>
#include<chrono>
#include<vector>
#include<list>
#include"engine/util/Constants.h"
#include"core/Subject.h"
#include"core/Observer.h"
#include"engine/objects/TexRenderer.h"
#include"engine/containers/ObjectManager.h"
#include"engine/util/Logger.h"
#include"game/EnemyShip.h"
#include"game/ActiveObjectTracker.h"

namespace sd_app {
namespace game {
namespace impl {
namespace enemy_ship_manager {
using namespace std::chrono;
using event_t = engine::constants::types::event_t;
using object_t = engine::constants::types::object_t;
template<class T>
using Subject = core::Subject<T>;
template<class T>
using Observer = core::Observer<T>;
template<class T>
using ObjectManager = engine::containers::ObjectManager<T>;
using DrawableObject = engine::objects::DrawableObject;
using Transform = engine::objects::Transform;
using TexRenderer = engine::objects::TexRenderer;
using GameObject = engine::objects::GameObject;
using Collider = engine::objects::Collider;
using RigidBody = engine::objects::RigidBody;
using Logger = engine::util::Logger;
using ShaderProgram = engine::util::ShaderProgram;



/** @addtogroup GameWorld */
/*@{*/
class EnemyShipManager :
  Subject<GameObject>,
  Observer<GameObject>,
  public ObjectManager<EnemyShip> {
public:
  EnemyShipManager(DrawableObject*, ShaderProgram*);
  ~EnemyShipManager();

  int MaxCapacity();
  int MaxActiveCapacity();
  std::vector<const EnemyShip*> ActiveEnemyShipList() const;

  void AddObserver(Observer*) override;
  void RemoveObserver(Observer*) override;
  void AddActiveObjectTracker(const ActiveObjectTracker*);

  int MinRespawnWaitTime() const;
  int MaxRespawnWaitTime() const;
  double MinProjectileSpeed() const;
  double MaxProjectileSpeed() const;
  float StartingYPos() const;
  double MinXPos() const;
  double MaxXPos() const;
  float TerminateYPos() const;
  float ProbabilityOfSpawn() const;
  int HitPoints() const;
  glm::vec3 ShipScale() const;
  int MaxPlacementAttempts() const;

  const Transform& GetTransform() const;
  Transform& GetTransform();

  void MinRespawnWaitTime(int);
  void MaxRespawnWaitTime(int);
  void MinProjectileSpeed(float);
  void MaxProjectileSpeed(float);
  void StartingYPos(float);
  void MinXPos(float);
  void MaxXPos(float);
  void TerminateYPos(float);
  void ProbabilityOfSpawn(float);
  void HitPoints(int);
  void ShipScale(const glm::vec3&);
  void ShipScale(float);
  void MaxPlacementAttempts(int);

  void Init() override;

protected:
  float mStartingYPos;
  float mTerminateYPos;
  float mProbabilityOfSpawn;
  int mMinRespawnWaitTime;
  int mMaxRespawnWaitTime;
  int mHitPoints;
  glm::vec3 mShipScale;
  Transform mTransform;
  DrawableObject* mShape;
  TexRenderer* mRenderer;
  std::map<unsigned int, unsigned int> mEnemyShipToIndexMap;
  std::random_device mRd;
  std::mt19937 mGen;
  std::uniform_real_distribution<> mSpawnDist;
  std::uniform_real_distribution<> mPosDist;
  std::uniform_real_distribution<> mSpeedDist;

  std::chrono::time_point<
    std::chrono::high_resolution_clock,
    std::chrono::duration<float, std::milli>> mLastSpawnTime;

  double mNextXPos;
  int mMaxPlacementAttempts;
  const ActiveObjectTracker* mTracker;
  Logger* mLogger;

  virtual void OnNotify(const GameObject&, const event_t&) override;
  EnemyShip* ConstructObject();
  void CustomAllocOps(unsigned int) override;
  void CustomDeallocOps(unsigned int) override;
  void CustomUpdateOps(float) override;
  bool DestructionPred(EnemyShip*) const override;

  void TrySpawn();
  bool CanSpawn();

};

/*@}*/
} // namespace enemy_ship_manager
} // namespace impl
using EnemyShipManager = impl::enemy_ship_manager::EnemyShipManager;
} // namespace game
} // namespace sd_app
#endif
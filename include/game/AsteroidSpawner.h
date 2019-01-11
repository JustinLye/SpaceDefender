#ifndef ASTEROID_SPAWNER_HEADER_INCLUDED
#define ASTEROID_SPAWNER_HEADER_INCLUDED
#include<random>
#include<chrono>
#include<vector>
#include"core/Subject.h"
#include"core/Observer.h"
#include"engine/containers/ObjectManager.h"
#include"engine/objects/RigidBody.h"
#include"engine/objects/TexRenderer.h"
#include"game/Asteroid.h"
#include"game/AsteroidCollision.h"
#include"game/ActiveObjectTracker.h"


namespace sd_app {
namespace game {
namespace impl {
namespace asteroid_spawner {
template<class T>
using Subject = core::Subject<T>;
template<class T>
using Observer = core::Observer<T>;
using event_t = engine::constants::types::event_t;
using object_t = engine::constants::types::object_t;
template<class T>
using ObjectManager = engine::containers::ObjectManager<T>;
using ShaderProgram = engine::util::ShaderProgram;
using DrawableObject = engine::objects::DrawableObject;
using Transform = engine::objects::Transform;
using TexRenderer = engine::objects::TexRenderer;
using GameObject = engine::objects::GameObject;
using Collider = engine::objects::Collider;
using RigidBody = engine::objects::RigidBody;

/** @addtogroup GameWorld */
/*@{*/


class AsteroidSpawner :
  Subject<GameObject>,
  Observer<GameObject>,
  public ObjectManager<Asteroid> {
public:
    
  AsteroidSpawner(DrawableObject*, ShaderProgram*);
  ~AsteroidSpawner();
  int MaxCapacity();
  int MaxActiveCapacity();
  std::vector<const Asteroid*> ActiveAsteroidList() const;

  void AddObserver(Observer*) override;
  void RemoveObserver(Observer*) override;
  void AddActiveObjectTracker(const ActiveObjectTracker*);

  int MinRespawnWaitTime() const;
  int MaxRespawnWaitTime() const;
  float MinProjectileSpeed() const;
  float MaxProjectileSpeed() const;
  float StartingYPos() const;
  float MinXPos() const;
  float MaxXPos() const;
  float TerminateYPos() const;
  float ProbabilityOfSpawn() const;
  float MinScale() const;
  float MaxScale() const;
  int MinHitPoints() const;
  int MaxHitPoints() const;
  float MinRotationSpeed() const;
  float MaxRotationSpeed() const;

  const Transform& GetTransform() const;
  Transform& GetTransform();

  void Scale(float);
  void Translate(const glm::vec3&);

  void MinRespawnWaitTime(int);
  void MaxRespawnWaitTime(int);
  void MinProjectileSpeed(float);
  void MaxProjectileSpeed(float);
  void StartingYPos(float);
  void MinXPos(float);
  void MaxXPos(float);
  void TerminateYPos(float);
  void ProbabilityOfSpawn(float);
  void MinScale(float);
  void MaxScale(float);
  void MinHitPoints(int);
  void MaxHitPoints(int);
  void MinRotationSpeed(float);
  void MaxRotationSpeed(float);

  void Init() override;

protected:
  float mStartingYPos;
  float mTerminateYPos;
  float mProbabilityOfSpawn;
  int mMinRespawnWaitTime;
  int mMaxRespawnWaitTime;
  int mMinHitPoints;
  int mMaxHitPoints;
  Transform mTransform;
  DrawableObject* mShape;
  TexRenderer* mRenderer;
  std::map<unsigned int, unsigned int> mAsteroidToIndexMap;
  std::random_device mRd;
  std::mt19937 mGen;
  std::uniform_real_distribution<> mSpawnDist;
  std::uniform_real_distribution<> mPosDist;
  std::uniform_real_distribution<> mSpeedDist;
  std::uniform_real_distribution<> mScaleDist;
  std::uniform_real_distribution<> mRotateDist;

  std::chrono::time_point<
    std::chrono::high_resolution_clock,
    std::chrono::duration<float, std::milli>> mLastSpawnTime;
  virtual void OnNotify(const GameObject&, const event_t&) override;
  Asteroid* ConstructObject();
  
  void CustomAllocOps(unsigned int) override;
  void CustomDeallocOps(unsigned int) override;
  void CustomUpdateOps(float) override;
  bool DestructionPred(Asteroid*) const override;

  void TrySpawn();
  Asteroid* LookUpAsteroid(unsigned int);

};
/*@}*/

} // namespace asteroid_spawner
} // namespace impl
using AsteroidSpawner = impl::asteroid_spawner::AsteroidSpawner;
} // namespace game
} // namespace sd_app


#endif

#ifndef EXPLOSION_MANAGER_HEADER_INCLUDED
#define EXPLOSION_MANAGER_HEADER_INCLUDED
#include<random>
#ifdef ENGINE_DEBUG
#include"engine/util//DebugFunctions.h"
#endif
#include"engine/util/Constants.h"
#include"engine/objects/TexRenderer.h"
#include"engine/containers/ObjectManager.h"
#include"game/Explosion.h"

namespace sd_app {
namespace game {
namespace impl {
namespace explosion_manager {
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
using Transform = engine::objects::Transform;
using Renderer = engine::objects::Renderer;
using TexRenderer = engine::objects::TexRenderer;
using ShaderProgram = engine::util::ShaderProgram;

class ExplosionManager :
  public Subject<GameObject>,
  public Observer<GameObject>,
  public ObjectManager<Explosion> {
public:
  ExplosionManager(DrawableObject*, ShaderProgram*);
  ~ExplosionManager();
  int MaxCapacity();
  int MaxActiveCapacity();
  virtual void OnNotify(const GameObject&, const event_t&) override;
  void AddObserver(Observer*) override;
  void RemoveObserver(Observer*) override;

  void ExpansionSpeed(float);
  void MinExpansion(float);
  void MaxExpansion(float);
  void InitScale(float);

  float ExpansionSpeed() const;
  float MaxExpansion() const;
  float MinExpansion() const;
  float InitScale() const;

protected:
  Transform mTransform;
  DrawableObject* mShape;
  ShaderProgram* mShaderProg;
  Renderer* mRenderer;
  float mSpeed;
  float mInitScale;
  std::random_device mRd;
  std::mt19937 mGen;
  std::uniform_real_distribution<> mExpansionDist;


  Explosion* ConstructObject();
  void CustomAllocOps(unsigned int) override;
  void CustomInitOps() override;
  bool DestructionPred(Explosion*) const override;
};

} // namespace explosion_manager
} // namespace impl
using ExplosionManager = impl::explosion_manager::ExplosionManager;
} // namespace game
} // namespace sd_app


#endif
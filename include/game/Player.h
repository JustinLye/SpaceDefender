#ifndef PLAYER_HEADER_INCLUDED
#define PLAYER_HEADER_INCLUDED
#include"engine/util/OpenGLUtility.h"
#include"engine/util/BoundryBox.h"
#include"engine/objects/GameObject.h"
#include"game/LaserCannon.h"

namespace sd_app {
namespace game {
namespace impl {
namespace player {
using event_t = engine::constants::types::event_t;
using object_t = engine::constants::types::object_t;
using direction_t = engine::constants::types::direction_t;

template<class T>
using Observer = core::Observer<T>;

using GameObject = engine::objects::GameObject;
using Collider = engine::objects::Collider;

using BoundryBox = engine::util::BoundryBox;
using OpenGLUtility = engine::util::OpenGLUtility;

/** @addtogroup GameActors */
/*@{*/
class Player :
  public GameObject {
public:
  Player();
  virtual ~Player();
  object_t Type() const override;
  void Render(const glm::mat4&, const glm::mat4&) override;
  void HandleKeyboardInput(GLFWwindow*);
  void AttachCannon(LaserCannon*);
  void Update(float) override;
  virtual void Strafe(const direction_t&);
  virtual void FireCannon();
  virtual void CustomScaleActions(float) override;
  virtual void CustomTranslateActions(const glm::vec3&) override;
  virtual void Speed(float);
  float Speed() const;
  virtual void Boost(float);
  float Boost() const;
  float CurrentGunTemp() const;
  float MaxGunTemp() const;
  bool GunOverHeated() const;

  virtual void DoDetection(Collider*);
  virtual void AddObserver(Observer<GameObject>*) override;
  virtual void RemoveObserver(Observer<GameObject>*) override;
protected:
  float mSpeed;
  float mStep;
  BoundryBox mBoundries;
  float mTargetXPos;
  float mSpeedBoost;
  float mMaxBoost;
  LaserCannon* mLaserCannon;
};
/*@}*/

} // namespace player
} // namespace impl
using Player = impl::player::Player;
} // namespace game
} // namespace sd_app


#endif
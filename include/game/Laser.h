#ifndef LASER_HEADER_INCLUDED
#define LASER_HEADER_INCLUDED
#ifdef ENGINE_DEBUG
#include"engine/util/DebugFunctions.h"
#endif
#include"engine/objects/GameObject.h"

namespace sd_app {
namespace game {
namespace impl {
namespace laser {
using namespace engine::constants::rendering;

using event_t = engine::constants::types::event_t;
using object_t = engine::constants::types::object_t;

using GameObject = engine::objects::GameObject;


/** @addtogroup GameComponents */
/*@{*/
class Laser :
  public GameObject {
public:
  Laser();
  ~Laser();
  object_t Type() const override;
  void Collide(const GameObject&) const override;
  void Update(float) override;
  void Render(const glm::mat4&, const glm::mat4&) override;
  void TerminateYPos(float);
  void Color(const glm::vec4&);

  float TerminateYPos() const;
  bool Terminate() const;
  const glm::vec4& Color() const;

protected:
  float mTerminateYPos;
  int mAttackDamage;
  glm::vec4 mColor;
};
/*@}*/
} // namespace laser
} // namespace impl
using Laser = impl::laser::Laser;
} // namespace game
} // namespace sd_app


#endif
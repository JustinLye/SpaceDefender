#ifndef EXPLOSION_HEADER_INCLUDED
#define EXPLOSION_HEADER_INCLUDED

#include"engine/objects/GameObject.h"

namespace sd_app {
namespace game {
namespace impl {
namespace explosion {
using event_t = engine::constants::types::event_t;
using object_t = engine::constants::types::object_t;
using GameObject = engine::objects::GameObject;

/** @addtogroup GameComponents */
/*@{*/

class Explosion :
  public GameObject {
public:
  Explosion();
  virtual ~Explosion();

  object_t Type() const override;
  virtual void Update(float) override;
  bool Terminate() const;

  void Speed(double);
  void MaxScale(double);

  double Speed() const;
  double MaxScale() const;

protected:
  double mSpeed;
  double mMaxScale;
};
/*@}*/
} // namespace explosion
} // namespace impl
using Explosion = impl::explosion::Explosion;
} // namespace game
} // namespace sd_app
#endif
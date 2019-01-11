#ifndef UI_OBJECT_HEADER_INCLUDED
#define UI_OBJECT_HEADER_INCLUDED

#include"core/Observer.h"
#include"engine/objects/GameObject.h"

namespace sd_app {
namespace engine {
namespace objects {
namespace impl {
namespace ui_object {
using event_t = constants::types::event_t;
template<class T>
using Observer = core::Observer<T>;

/** @addtogroup EngineObjects */
/*@{*/

class UIObject :
  public Observer<GameObject> {
public:
  UIObject();
  virtual ~UIObject();
  virtual void Render() = 0;
  virtual void OnNotify(const GameObject&, const event_t&) override;
};
/*@}*/
} // namespace ui_object
} // namespace impl
using UIObject = impl::ui_object::UIObject;
} // namespace objects
} // namespace engine
} // namespace sd_app

#endif
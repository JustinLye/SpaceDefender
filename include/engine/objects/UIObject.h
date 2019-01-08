#ifndef UI_OBJECT_HEADER_INCLUDED
#define UI_OBJECT_HEADER_INCLUDED

#include"engine/objects/Observer.h"
namespace sd_app {
namespace engine {
namespace objects {
namespace impl {
namespace ui_object {
class GameObject;
using event_t = constants::types::event_t;

/** @addtogroup EngineObjects */
/*@{*/

class UIObject :
  public Observer {
public:
  UIObject();
  virtual ~UIObject();
  virtual void Render() = 0;
  virtual void OnNotify(const GameObject&, const event_t&);
};
/*@}*/
} // namespace ui_object
} // namespace impl
using UIObject = impl::ui_object::UIObject;
} // namespace objects
} // namespace engine
} // namespace sd_app

#endif
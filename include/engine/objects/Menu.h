#ifndef MENU_HEADER_INCLUDED
#define MENU_HEADER_INCLUDED

#include"engine/objects/Subject.h"
#include"engine/objects/Transform.h"
#include"engine/objects/Canvas.h"

namespace sd_app {
namespace engine {
namespace objects {
namespace impl {
namespace menu {
class Menu :
  public Subject,
  public Canvas {
public:
  Menu();
  virtual ~Menu();
  Transform& GetTransform();
protected:

};

/*@}*/
} // namespace menu
} // namespace impl
using Menu = impl::menu::Menu;
} // namespace objects
} // namespace engine
} // namespace sd_app

/** @addtogroup EngineObjects */
/*@{*/


#endif
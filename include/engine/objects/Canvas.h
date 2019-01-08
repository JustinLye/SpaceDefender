#ifndef CANVAS_HEADER_INCLUDED
#define CANVAS_HEADER_INCLUDED
#include<map>
#include"engine/objects/UIObject.h"
#include"engine/objects/Text.h"

namespace sd_app {
namespace engine {
namespace objects {
namespace impl {
namespace canvas {
/** @addtogroup EngineObjects */
/*@{*/
class Canvas :
  public UIObject {
public:
  Canvas();
  virtual ~Canvas();
  void Render();

  void AddUIObject(UIObject*);
  void RemoveUIObject(UIObject*);

protected:
  std::map<unsigned int, UIObject*> mUIObjects;
};

/*@}*/

} // namespace canvas
} // namespace impl
using Canvas = impl::canvas::Canvas;
} // namespace objects
} // namespace engine
} // namespace sd_app


#endif

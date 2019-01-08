#ifndef RECTANGLE_HEADER_INCLUDED
#define RECTANGLE_HEADER_INCLUDED

namespace sd_app {
namespace engine {
namespace shapes {
namespace impl {
namespace rectangle {
/** @addtogroup EngineShapes */
/*@{*/
struct Origin {
  float x;
  float y;
};

struct Size {
  float x;
  float y;
};

struct Rectangle {
  Origin mOrigin;
  Size mSize;
};
/*@}*/
} // namespace rectangle
} // namespace impl
using Rectangle = impl::rectangle::Rectangle;
} // namespace shapes
} // namespace engine
} // namespace sd_app

#endif
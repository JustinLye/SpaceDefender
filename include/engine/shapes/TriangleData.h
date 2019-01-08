#ifndef TRIANGLE_DATA_HEADER_INCLUDED
#define TRIANGLE_DATA_HEADER_INCLUDED

#include"engine/shapes/ShapeData.h"
namespace sd_app {
namespace engine {
namespace shapes {
namespace impl {
namespace triangle_data {
/** @addtogroup EngineShapes */
/*@{*/

class TriangleData :
  public ShapeData {
public:
  TriangleData();
  virtual ~TriangleData();
  unsigned int VertCount();
  unsigned int IndexCount();
  GLenum PrimType();

protected:
  void InitializeData();

};
/*@}*/
} // namespace triangle_data
} // namespace impl
using TriangleData = impl::triangle_data::TriangleData;
} // namespace shapes
} // namespace engine
} // namespace sd_app

#endif
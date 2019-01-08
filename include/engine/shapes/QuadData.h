#ifndef QUAD_DATA_HEADER_INCLUDED
#define QUAD_DATA_HEADER_INCLUDED

#include"engine/shapes/ShapeData.h"
namespace sd_app {
namespace engine {
namespace shapes {
namespace impl {
namespace quad_data {
/** @addtogroup EngineShapes */
/*@{*/

class QuadData :
  public ShapeData {
public:
  QuadData();
  virtual ~QuadData();
  unsigned int VertCount();
  unsigned int IndexCount();
  GLenum PrimType();
protected:
  virtual void InitializeData();
};
/*@}*/
} // namespace quad_data
} // namespace impl
using QuadData = impl::quad_data::QuadData;
} // namespace shapes
} // namespace engine
} // namespace sd_app

#endif
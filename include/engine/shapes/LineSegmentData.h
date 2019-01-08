#ifndef LINE_SEGMENT_DATA_HEADER_INCLUDED
#define LINE_SEGMENT_DATA_HEADER_INCLUDED

#include"engine/shapes/ShapeData.h"

namespace sd_app {
namespace engine {
namespace shapes {
namespace impl {
namespace line_segment_data {
/** @addtogroup EngineShapes */
/*@{*/

class LineSegmentData :
  public ShapeData {
public:
  LineSegmentData();
  virtual ~LineSegmentData();
  unsigned int VertCount();
  unsigned int IndexCount();
  GLenum PrimType();
protected:
  void InitializeData();
};
/*@}*/
} // namespace line_segment_data
} // namespace impl
using LineSegmentData = impl::line_segment_data::LineSegmentData;
} // namespace shapes
} // namespace engine
} // namespace sd_app


#endif
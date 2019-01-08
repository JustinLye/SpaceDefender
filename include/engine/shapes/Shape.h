#ifndef	SHAPE_HEADER_INCLUDED
#define SHAPE_HEADER_INCLUDED
#ifdef ENGINE_DEBUG
#include<iostream>
#endif
#include<memory>
#include"engine/util/Constants.h"
#include"engine/shapes/ShapeData.h"
#include"engine/objects/DrawableObject.h"

namespace sd_app {
namespace engine {
namespace shapes {
namespace impl {
namespace shape {
using DrawableObject = objects::DrawableObject;
using namespace constants::shaders;
/** @addtogroup EngineShapes */
/*@{*/
class Shape :
  public DrawableObject {
public:
  Shape();
  virtual ~Shape();
  virtual void Draw();
  virtual void ShapeDataPtr(ShapeData*);
  virtual void Buffer(ShapeData* = nullptr);

protected:
  ShapeData* mShapeData;
  GLuint mVerticesVboId;
  GLuint mIndicesVboId;
  virtual void Destroy();
};
/*@}*/
} // namespace shape
} // namespace impl
using Shape = impl::shape::Shape;
} // namespace shapes
} // namespace engine
} // namespace sd_app


#endif
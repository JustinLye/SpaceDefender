#ifndef SHAPE_DATA_HEADER_INCLUDED
#define SHAPE_DATA_HEADER_INCLUDED
#ifdef ENGINE_DEBUG
#include<iostream>
#endif
#include<glm/glm.hpp>
#include<glad/glad.h>

namespace sd_app {
namespace engine {
namespace shapes {
namespace impl {
namespace shape_data {
/** @addtogroup EngineShapes */
/*@{*/

class ShapeData {
public:
  ShapeData();
  virtual ~ShapeData();
  virtual unsigned int VertCount() = 0;
  virtual unsigned int IndexCount() = 0;
  virtual GLenum PrimType() = 0;
  virtual void FillVertices(GLfloat*);
  virtual void FillIndices(GLuint*);

protected:
  glm::vec3* mVertices;
  GLuint* mIndices;
  virtual void Init();
  virtual void InitializePointers();
  virtual void InitializeData() = 0;
  virtual void Destroy();
};
/*@}*/
} // namespace shape_data
} // namespace impl
using ShapeData = impl::shape_data::ShapeData;
} // namespace shapes
} // namespace engine
} // namespace sd_app


#endif
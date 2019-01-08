#ifndef TEX_DATA_HEADER_INCLUDED
#define TEX_DATA_HEADER_INCLUDED

#include<glm/glm.hpp>
#include<glad/glad.h>

namespace sd_app {
namespace engine {
namespace graphics {
namespace impl {
namespace tex_data {
/** @addtogroup EngineGraphics */
/*@{*/

struct TexVertexData {
  glm::vec3 mVertices;
  glm::vec2 mUV;
};

class TexData {
public:
  TexData();
  virtual ~TexData();
  virtual unsigned int VertCount() = 0;
  virtual unsigned int IndexCount() = 0;
  virtual GLenum PrimType() = 0;
  virtual void FillVertices(GLfloat*);
  virtual void FillIndices(GLuint*);
protected:
  TexVertexData* mTexVertexData;
  GLuint* mIndices;
  virtual void Init();
  virtual void InitializePointers();
  virtual void InitializeData() = 0;
  virtual void Destroy();
};

/*@}*/
} // namespace tex_data
} // namespace impl
using TexVertexData = impl::tex_data::TexVertexData;
using TexData = impl::tex_data::TexData;
} // namespace graphics
} // namespace engine
} // namespace ad_app


#endif
#ifndef TEX_RENDERER_HEADER_INCLUDED
#define TEX_RENDERER_HEADER_INCLUDED

#include<glad/glad.h>
#include<glm/glm.hpp>
#include"engine/objects/Renderer.h"

namespace sd_app {
namespace engine {
namespace objects {
namespace impl {
namespace tex_renderer {
using namespace constants::rendering;
using namespace constants::shaders;
using ShaderProgram = util::ShaderProgram;
using OpenGLPolyMode = util::OpenGLPolyMode;
using OpenGLOptions = util::OpenGLOptions;

/** @addtogroup EngineObjects */
/*@{*/

class TexRenderer :
  public Renderer {
public:
  TexRenderer(ShaderProgram* = nullptr, const OpenGLPolyMode& = OpenGLOptions::DEFAULT_POLY_MODE);
  virtual ~TexRenderer();
  virtual void SetCustomUniforms() override;

  const bool UseMixInColor() const;
  const glm::vec4& MixInColor() const;

  void UseMixInColor(bool);
  void MixInColor(const glm::vec4&);
protected:
  int mUseMixInColor;
  glm::vec4 mMixInColor;
};
/*@}*/
} // namespace tex_renderer
} // namespace impl
using TexRenderer = impl::tex_renderer::TexRenderer;
} // namespace objects
} // namespace engine
} // namespace sd_app


#endif
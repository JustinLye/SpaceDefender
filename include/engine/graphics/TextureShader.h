
#ifndef TEXTURE_SHADER_HEADER_INCLUDED
#define TEXTURE_SHADER_HEADER_INCLUDED

#include"engine/util/Paths.h"
#include"engine/util/Constants.h"
#include"engine/util/ShaderProgram.h"
#define STB_IMAGE_IMPLEMENTATION
#include"engine/graphics/Texture.h" //for sizeof(TexVertexData)

namespace sd_app {
namespace engine {
namespace graphics {
namespace impl {
namespace texture_shader {
using namespace constants::shaders;
using ShaderProgram = sd_app::engine::util::ShaderProgram;

class TextureShader :
  public ShaderProgram {
public:
  TextureShader();
  virtual ~TextureShader();
  virtual void Init() override;
};
} // namespace texture_shader
} // namespace impl
using TextureShader = impl::texture_shader::TextureShader;
} // namespace graphics
} // namespace engine
} // namespace sd_app


#endif
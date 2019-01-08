#ifndef TEXT_SHADER_HEADER_INCLUDED
#define TEXT_SHADER_HEADER_INCLUDED

#include"engine/util/Constants.h"
#include"engine/util/ShaderProgram.h"

namespace sd_app {
namespace engine {
namespace util {
namespace impl {
namespace text_shader {
using namespace constants::shaders;
/** @addtogroup EngineUtil */
/*@{*/
class TextShader :
  public ShaderProgram {
public:
  TextShader();
  virtual ~TextShader();
  virtual void Init() override;
};
/*@}*/
} // namespace text_shader
} // namespace impl
using TextShader = impl::text_shader::TextShader;
} // namespace util
} // namespace engine
} // namespace sd_app



#endif

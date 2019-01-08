#ifndef FONT_DATA_HEADER_INCLUDED
#define FONT_DATA_HEADER_INCLUDED

#include<map>
#include<string>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<ft2build.h>
#include FT_FREETYPE_H


namespace sd_app {
namespace engine {
namespace font {
namespace impl {
namespace font_data {
/** @addtogroup EngineFonts */
/*@{*/

struct Character {
  GLuint mTextureId;
  glm::ivec2 mSize;
  glm::ivec2 mBearing;
  GLuint mAdvance;
};

class FontData {
public:
  FontData();
  virtual ~FontData();
  virtual const char* PathToFont() = 0;
  virtual int Width() = 0;
  virtual int Height() = 0;
  void Init();
  void Destroy();
  const Character& operator[](const GLchar&) const;
protected:
  std::map<GLchar, Character> mCharacterMap;
  GLuint* mTextures;
};
/*@}*/
} // namespace font_data
} // namespace impl
using Character = impl::font_data::Character;
using FontData = impl::font_data::FontData;
} // namespace font
} // namespace engine
} // namespace sd_app


#endif

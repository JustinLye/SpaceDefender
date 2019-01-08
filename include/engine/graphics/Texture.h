#ifndef TEXTURE_HEADER_INCLUDED
#define TEXTURE_HEADER_INCLUDED
#ifdef GRAPHICS_DEBUG
#include"engine/util/DebugFunctions.h"
#endif
#include<string>
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include"stb/stb_image.h"
#endif
#include"engine/util/Constants.h"
#include"engine/graphics/TexData.h"
#include"engine/objects/DrawableObject.h"

namespace sd_app {
namespace engine {
namespace graphics {
namespace impl {
namespace texture {

using namespace constants::shaders;

/** @addtogroup EngineGraphics */
/*@{*/

class Texture :
	public TexData,
	public DrawableObject
{
public:
	Texture();
	virtual ~Texture();
	unsigned int VertCount();
	unsigned int IndexCount();
	GLenum PrimType();

	virtual void Draw();
	virtual void Buffer();
	virtual void LoadFromFile(const std::string&);
	const unsigned int& TexId() const;

protected:
	unsigned int mTexId;
	GLuint mVerticesVboId;
	GLuint mIndicesVboId;

	void InitializeData();
	virtual void CustomActivationSteps();
	virtual void CustomDeactivationSteps();


};
/*@}*/
} // namespace texture
} // namespace impl
using Texture = impl::texture::Texture;
} // namespace graphics
} // namespace engine
} // namespace ad_app
#endif
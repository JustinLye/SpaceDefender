
#ifndef TEXTURE_SHADER_HEADER_INCLUDED
#define TEXTURE_SHADER_HEADER_INCLUDED

#include"engine/util/Paths.h"
#include"engine/util/Constants.h"
#include"engine/util/ShaderProgram.h"
#define STB_IMAGE_IMPLEMENTATION
#include"engine/graphics/Texture.h" //for sizeof(TexVertexData)


using namespace Constants::Shaders;

class TextureShader :
	public ShaderProgram
{
public:
	TextureShader();
	virtual ~TextureShader();
	virtual void Init() override;
};

#endif
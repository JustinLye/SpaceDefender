#include"engine/graphics/TextureShader.h"

TextureShader::TextureShader() :
	ShaderProgram()
{

}

TextureShader::~TextureShader()
{

}

void TextureShader::Init()
{
	std::string vshader = EngineShaderPath(TEXTURE_VERT_SHADER);
	std::string fshader = EngineShaderPath(TEXTURE_FRAG_SHADER);
	LoadFromFile(VERTEX, vshader);
	LoadFromFile(FRAGMENT, fshader);
	CreateAndLink();
	Use();
	AddAttribute(DFLT_VERTEX_ATTRIB_NAME);
	AddAttribute(TEXTURE_COORD_ATTRIB_NAME);
	AutoFillUniformsFromFile(vshader);
	AutoFillUniformsFromFile(fshader);
	glEnableVertexAttribArray((*this)[DFLT_VERTEX_ATTRIB_NAME]);
	glVertexAttribPointer((*this)[DFLT_VERTEX_ATTRIB_NAME], 3, GL_FLOAT, GL_FALSE, sizeof(TexVertexData), 0);
	glEnableVertexAttribArray((*this)[TEXTURE_COORD_ATTRIB_NAME]);
	glVertexAttribPointer((*this)[TEXTURE_COORD_ATTRIB_NAME], 2, GL_FLOAT, GL_FALSE, sizeof(TexVertexData), (void*)(sizeof(glm::vec3)));
}
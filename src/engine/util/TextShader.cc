#include"engine/util/TextShader.h"

TextShader::TextShader() :
	ShaderProgram()
{

}

TextShader::~TextShader()
{

}

void TextShader::Init()
{
	std::string vshader = EngineShaderPath(Constants::Shaders::DFLT_VERTEX_SHADER);
	std::string fshader = EngineShaderPath(Constants::Shaders::DFLT_FRAGMENT_SHADER);
	LoadFromFile(ShaderProgram::VERTEX, vshader);
	LoadFromFile(ShaderProgram::FRAGMENT, fshader);
	CreateAndLink();
	Use();
	AutoFillUniformsFromFile(vshader);
	AutoFillUniformsFromFile(fshader);
	glEnableVertexAttribArray(this->operator[](Constants::Shaders::DFLT_VERTEX_ATTRIB_NAME));
	glVertexAttribPointer(this->operator[](Constants::Shaders::DFLT_VERTEX_ATTRIB_NAME), 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), 0);
	UnUse();
}
#include"engine/util/TextShader.h"
namespace sd_app {
namespace engine {
namespace util {
namespace impl {
namespace text_shader {
TextShader::TextShader() :
	ShaderProgram()
{

}

TextShader::~TextShader()
{

}

void TextShader::Init()
{
	std::string vshader = EngineShaderPath(TEXT_VERTEX_SHADER);
	std::string fshader = EngineShaderPath(TEXT_FRAGMENT_SHADER);
	LoadFromFile(ShaderProgram::VERTEX, vshader);
	LoadFromFile(ShaderProgram::FRAGMENT, fshader);
	CreateAndLink();
	Use();
	AutoFillUniformsFromFile(vshader);
	AutoFillUniformsFromFile(fshader);
	std::cout << __FUNCTION__ << " " << __LINE__ << '\n';
	glEnableVertexAttribArray(this->operator[](DFLT_VERTEX_ATTRIB_NAME));
	glVertexAttribPointer(this->operator[](DFLT_VERTEX_ATTRIB_NAME), 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), 0);
	UnUse();
}

} // namespace text_shader
} // namespace impl
} // namespace util
} // namespace engine
} // namespace sd_app
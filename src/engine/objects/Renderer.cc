#include"engine/objects/Renderer.h"

const GLenum Renderer::DFLT_POLY_MODE = GL_LINES;

Renderer::Renderer(const GLenum& poly_mode) :
	mShader(ShaderProgram()),
	mPolyMode(poly_mode),
	mColor(Constants::Rendering::DFLT_SHAPE_COLOR)
{
	Init();
}

Renderer::~Renderer()
{
	Destroy();
}

void Renderer::Render(Shape* shape, const float* MVP)
{
	mShader.Use();
	glBindVertexArray(shape->GetVAO());
	glUniformMatrix4fv(mShader(Constants::Shaders::DFLT_MVP_UNIFORM_NAME), 1, GL_FALSE, MVP);
	SetCustomUniforms();
	GLint prev_poly_mode;
	glGetIntegerv(GL_POLYGON_MODE, &prev_poly_mode);
	glPolygonMode(GL_FRONT_AND_BACK, mPolyMode);
	shape->Draw();
	glBindVertexArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, prev_poly_mode);
	mShader.UnUse();

}

std::string Renderer::VertexShaderPath()
{
	return EngineShaderPath(Constants::Shaders::DFLT_VERTEX_SHADER);
}

std::string Renderer::FragmentShaderPath()
{
	return EngineShaderPath(Constants::Shaders::DFLT_FRAGMENT_SHADER);
}

void Renderer::SetCustomUniforms()
{
	glUniform4fv(mShader(Constants::Shaders::DFLT_COLOR_UNIFORM_NAME), 1, glm::value_ptr(mColor));
}

void Renderer::SetAttribs()
{
	mShader.AddAttribute(Constants::Shaders::DFLT_VERTEX_ATTRIB_NAME);
}

void Renderer::Init()
{
	mShader.LoadFromFile(ShaderProgram::VERTEX, VertexShaderPath());
	mShader.LoadFromFile(ShaderProgram::FRAGMENT, FragmentShaderPath());
	mShader.CreateAndLink();
	mShader.Use();
	SetAttribs();
	mShader.AutoFillUniformsFromFile(VertexShaderPath());
	mShader.AutoFillUniformsFromFile(FragmentShaderPath());
	SetCustomUniforms();
	glEnableVertexAttribArray(mShader[Constants::Shaders::DFLT_VERTEX_ATTRIB_NAME]);
	glVertexAttribPointer(mShader[Constants::Shaders::DFLT_VERTEX_ATTRIB_NAME], 3, GL_FLOAT, GL_FALSE, 0, 0);
	mShader.UnUse();
}

void Renderer::Destroy()
{
	mShader.DeleteProgram();
}



void Renderer::PolyMode(const GLenum& poly_mode)
{
	mPolyMode = poly_mode;
}

const GLenum& Renderer::PolyMode() const
{
	return mPolyMode;
}

void Renderer::Color(const glm::vec4& color)
{
	mColor = color;
}

const glm::vec4& Renderer::Color() const
{
	return mColor;
}
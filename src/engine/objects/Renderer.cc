#include"engine/objects/Renderer.h"

Renderer::Renderer(ShaderProgram* shader_program, const GLenum& poly_mode) :
	mShader(shader_program),
	mPolyMode(poly_mode),
	mColor(DFLT_SHAPE_COLOR)
{
	if (shader_program != nullptr)
	{
		Init();
	}
}

Renderer::~Renderer()
{
	Destroy();
}

void Renderer::Render(Shape* shape, const float* MVP)
{
#ifdef ENGINE_DEBUG
	assert(mShader != nullptr);
#endif
	mShader->Use();
	glBindVertexArray(shape->GetVAO());
	glUniformMatrix4fv(mShader->operator()(DFLT_MVP_UNIFORM_NAME), 1, GL_FALSE, MVP);
	SetCustomUniforms();
	GLint prev_poly_mode;
	glGetIntegerv(GL_POLYGON_MODE, &prev_poly_mode);
	glPolygonMode(GL_FRONT_AND_BACK, mPolyMode);
	shape->Draw();
	glBindVertexArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, prev_poly_mode);
	mShader->UnUse();

}

std::string Renderer::VertexShaderPath()
{
	return EngineShaderPath(DFLT_VERTEX_SHADER);
}

std::string Renderer::FragmentShaderPath()
{
	return EngineShaderPath(DFLT_FRAGMENT_SHADER);
}

void Renderer::SetCustomUniforms()
{
	glUniform4fv(mShader->operator()(DFLT_COLOR_UNIFORM_NAME), 1, glm::value_ptr(mColor));
}

void Renderer::SetAttribs()
{
	mShader->AddAttribute(DFLT_VERTEX_ATTRIB_NAME);
}

void Renderer::Init()
{
#ifdef ENGINE_DEBUG
	assert(mShader != nullptr);
#endif
	mShader->Use();
	SetAttribs();
	SetCustomUniforms();
	mShader->UnUse();

}

void Renderer::Destroy()
{

}

void Renderer::Shader(ShaderProgram* shader)
{
	mShader = shader;
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
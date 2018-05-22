 #include"engine/objects/Renderer.h"

Renderer::Renderer(ShaderProgram* shader_program, const OpenGLPolyMode& poly_mode) :
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

void Renderer::Render(DrawableObject* object, const float* MVP)
{
#ifdef ENGINE_DEBUG
	assert(mShader != nullptr);
#endif
	mShader->Use();
	object->Activate();
	glUniformMatrix4fv(mShader->operator()(DFLT_MVP_UNIFORM_NAME), 1, GL_FALSE, MVP);
	SetCustomUniforms();
	glPolygonMode(GL_FRONT, mPolyMode[OpenGLPolyMode::face_t::FRONT]);
	glPolygonMode(GL_BACK, mPolyMode[OpenGLPolyMode::face_t::BACK]);
	object->Draw();
	object->Deactivate();
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


void Renderer::PolyMode(const OpenGLPolyMode::face_t& face, const GLenum& poly_mode)
{
	mPolyMode[face] = poly_mode;
}

const GLenum& Renderer::PolyMode(const OpenGLPolyMode::face_t& face) const
{
	return mPolyMode[face];
}


void Renderer::Color(const glm::vec4& color)
{
	mColor = color;
}

const glm::vec4& Renderer::Color() const
{
	return mColor;
}
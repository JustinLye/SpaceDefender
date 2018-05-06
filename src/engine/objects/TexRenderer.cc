#include"engine/objects/TexRenderer.h"

TexRenderer::TexRenderer(ShaderProgram* shader_prog, const GLenum& poly_mode) :
	Renderer(nullptr, poly_mode)
{
	mShader = shader_prog;
	Init();
}

TexRenderer::~TexRenderer()
{

}

void TexRenderer::SetCustomUniforms()
{
	glUniform1i((*mShader)(TEXTURE_SAMPLER_NAME), 0);
}
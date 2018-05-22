#include"engine/objects/TexRenderer.h"

TexRenderer::TexRenderer(ShaderProgram* shader_prog, const OpenGLPolyMode& poly_mode) :
	Renderer(nullptr, poly_mode),
	mUseMixInColor(0),
	mMixInColor(glm::vec4(DFLT_SHAPE_COLOR.x, DFLT_SHAPE_COLOR.y, DFLT_SHAPE_COLOR.z, 0.0f))
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
	glUniform1i((*mShader)(USE_MIX_IN_COLOR_NAME), mUseMixInColor);
	glUniform4fv((*mShader)(MIX_IN_COLOR_NAME), 1, glm::value_ptr(mMixInColor));
}

const bool TexRenderer::UseMixInColor() const
{
	if (mUseMixInColor == 1)
	{
		return true;
	}
	return false;
}

const glm::vec4& TexRenderer::MixInColor() const
{
	return mMixInColor;
}

void TexRenderer::UseMixInColor(bool use)
{
	if (use)
	{
		mUseMixInColor = 1;
	}
	else
	{
		mUseMixInColor = 0;
	}
}

void TexRenderer::MixInColor(const glm::vec4& color)
{
	mMixInColor = color;
}
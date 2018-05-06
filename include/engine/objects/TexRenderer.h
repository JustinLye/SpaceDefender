#ifndef TEX_RENDERER_HEADER_INCLUDED
#define TEX_RENDERER_HEADER_INCLUDED

#include<glad/glad.h>
#include<glm/glm.hpp>
#include"engine/objects/Renderer.h"

class TexRenderer :
	public Renderer
{
public:
	TexRenderer(ShaderProgram* = nullptr, const GLenum& = DFLT_POLY_MODE);
	virtual ~TexRenderer();
	virtual void SetCustomUniforms() override;
};

#endif
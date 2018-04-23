#ifndef TEXT_RENDERER_HEADER_INCLUDED
#define TEXT_RENDERER_HEADER_INCLUDED

#include"engine/objects/Renderer.h"
#include"engine/font/Font.h"

class TextRenderer :
	protected Renderer
{
public:
	using Renderer::Shader;
	using Renderer::PolyMode;
	using Renderer::Color;
	using Renderer::Init;
	
	TextRenderer(ShaderProgram* = nullptr, const GLenum& = DFLT_POLY_MODE);
	virtual ~TextRenderer();
	virtual void Render(Font*, const std::string&, const GLfloat&, const GLfloat&, const GLfloat&, const glm::vec3&);
};

#endif
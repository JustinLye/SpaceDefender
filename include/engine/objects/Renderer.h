#ifndef RENDERER_HEADER_INCLUDED
#define RENDERER_HEADER_INCLUDED
#include<map>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"engine/util/ShaderProgram.h"
#include"engine/shapes/Shape.h"

// NOTE: Renderer should use a pointer to ShaderProgram and not have its' own instance

class Renderer
{
public:
	Renderer(const GLenum& = DFLT_POLY_MODE);
	virtual ~Renderer();
	virtual void Render(const float* MVP);
	virtual std::string VertexShaderPath();
	virtual std::string FragmentShaderPath();
	virtual void SetCustomUniforms();
	virtual void SetAttribs();
	virtual void Init();
	virtual void Destroy();


	void PolyMode(const GLenum&);
	const GLenum& PolyMode() const;

	void Color(const glm::vec4&);
	const glm::vec4& Color() const;

	static const GLenum DFLT_POLY_MODE;

protected:
	
	ShaderProgram mShader;
	GLenum mPolyMode;
	glm::vec4 mColor;
};

#endif
#ifndef RENDERER_HEADER_INCLUDED
#define RENDERER_HEADER_INCLUDED
#include<map>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"engine/util/Constants.h"
#include"engine/util/ShaderProgram.h"
#include"engine/shapes/Shape.h"

using namespace Constants::Shaders;
using namespace Constants::Rendering;
class Renderer
{
public:
	Renderer(ShaderProgram* = nullptr, const GLenum& = DFLT_POLY_MODE);
	virtual ~Renderer();
	virtual void Render(Shape*, const float*);
	virtual std::string VertexShaderPath();
	virtual std::string FragmentShaderPath();
	virtual void SetCustomUniforms();
	virtual void SetAttribs();
	virtual void Init();
	virtual void Destroy();

	virtual void Shader(ShaderProgram*);

	void PolyMode(const GLenum&);
	const GLenum& PolyMode() const;

	void Color(const glm::vec4&);
	const glm::vec4& Color() const;
protected:
	
	ShaderProgram* mShader;
	GLenum mPolyMode;
	glm::vec4 mColor;
};

#endif
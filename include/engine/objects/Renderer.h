#ifndef RENDERER_HEADER_INCLUDED
#define RENDERER_HEADER_INCLUDED
#include<map>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"engine/util/OpenGLOptions.h"
#include"engine/util/UtiliDefs.h"
#include"engine/util/Constants.h"
#include"engine/util/ShaderProgram.h"
#include"engine/shapes/Shape.h"

using namespace Constants::Shaders;
using namespace Constants::Rendering;
/** @addtogroup EngineObjects */
/*@{*/
class Renderer
{
public:
	Renderer(ShaderProgram* = nullptr, const OpenGLPolyMode& = OpenGLOptions::DEFAULT_POLY_MODE);
	virtual ~Renderer();
	virtual void Render(DrawableObject*, const float*);
	virtual std::string VertexShaderPath();
	virtual std::string FragmentShaderPath();
	virtual void SetCustomUniforms();
	virtual void SetAttribs();
	virtual void Init();
	virtual void Destroy();

	virtual void Shader(ShaderProgram*);

	void PolyMode(const OpenGLPolyMode::face_t&, const GLenum&);
	const GLenum& PolyMode(const OpenGLPolyMode::face_t&) const;

	void Color(const glm::vec4&);
	const glm::vec4& Color() const;
protected:
	
	ShaderProgram* mShader;
	OpenGLPolyMode mPolyMode;
	glm::vec4 mColor;
};
/*@}*/
#endif
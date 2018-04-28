#ifndef FONT_HEADER_INCLUDED
#define FONT_HEADER_INCLUDED
#include<glm/gtc/type_ptr.hpp>
#include"engine/util/Constants.h"
#include"engine/util/ShaderProgram.h"
#include"engine/font/FontData.h"
using namespace Constants::Shaders;

class Font
{
public:
	Font();
	virtual ~Font();
	void Data(FontData*);
	FontData* Data();
	void Shader(ShaderProgram*);
	ShaderProgram* Shader();
	void Color(const glm::vec4&);
	const glm::vec4& Color() const;
	virtual void Render(const std::string&, const GLfloat&, const GLfloat&, const GLfloat&);
	virtual void Init();
	virtual void Destroy();
	const GLuint& GetVao() const;
	void Projection(const glm::mat4&);
	const glm::mat4& Projection() const;
protected:
	ShaderProgram* mShader;
	FontData* mFontData;
	GLuint mVaoId;
	GLuint mVboId;
	glm::vec4 mColor;
	glm::mat4 mProjection;
};

#endif
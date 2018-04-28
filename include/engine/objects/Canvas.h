#ifndef CANVAS_HEADER_INCLUDED
#define CANVAS_HEADER_INCLUDED
#include<memory>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"engine/util/ShaderProgram.h"
#include"engine/font/Font.h"
class Canvas
{
public:
	Canvas();
	virtual ~Canvas();
	virtual float ScreenWidth() = 0;
	virtual float ScreenHeight() = 0;
	void Init();
	void Destroy();
	void Render(const std::string&, const GLfloat&, const GLfloat&, const GLfloat&, const glm::vec3&);
	ShaderProgram mShader;
	glm::mat4 mProjection;
	std::shared_ptr<Font> mFont;
protected:
	GLuint mVaoId;
	GLuint mVboVerticesId;

};


#endif

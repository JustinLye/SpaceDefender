#ifndef FONT_HEADER_INCLUDED
#define FONT_HEADER_INCLUDED
#ifdef FONT_DEBUG
#include<iostream>
#endif
#include<map>
#include<string>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<ft2build.h>
#include FT_FREETYPE_H

struct Character
{
	GLuint mTextureId;
	glm::ivec2 mSize;
	glm::ivec2 mBearing;
	GLuint mAdvance;
};

class Font
{
public:
	Font();
	virtual ~Font();
	virtual const char* PathToFont() = 0;
	virtual int FontWidth() = 0;
	virtual int FontHeight() = 0;
	void Draw(const std::string&, const GLfloat&, const GLfloat&, const GLfloat&);
	void Init();
	void Buffer();
	void Destroy();
	const Character& operator[](const GLchar&) const;
protected:
	std::map<GLchar, Character> mCharacterMap;
private:
	static bool InitOpenGL;
	GLuint* mTextures;
	GLuint mVaoId;
	GLuint mVboId;
};






#endif
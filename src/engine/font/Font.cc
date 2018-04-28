#include"engine/font/Font.h"


Font::Font() :
	mShader(nullptr),
	mFontData(nullptr),
	mVaoId(0),
	mVboId(0),
	mColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
	mProjection(glm::mat4(1.0f))
{

}

Font::~Font()
{
	Destroy();
}

void Font::Data(FontData* font_data)
{
	mFontData = font_data;
}

FontData* Font::Data()
{
	return mFontData;
}

void Font::Shader(ShaderProgram* shader)
{
	mShader = shader;
}

ShaderProgram* Font::Shader()
{
	return mShader;
}

void Font::Color(const glm::vec4& color)
{
	mColor = color;
}

const glm::vec4& Font::Color() const
{
	return mColor;
}

void Font::Projection(const glm::mat4& proj)
{
	mProjection = proj;
}

const glm::mat4& Font::Projection() const
{
	return mProjection;
}

void Font::Render(const std::string& text, const GLfloat& x, const GLfloat& y, const GLfloat& scale)
{
	mShader->Use();
	glBindVertexArray(mVaoId); 
	glUniform4fv((*mShader)(TEXT_COLOR_UNIFORM_NAME), 1, glm::value_ptr(mColor));
	glUniformMatrix4fv((*mShader)(TEXT_PROJ_UNIFORM_NAME), 1, GL_FALSE, glm::value_ptr(mProjection));
	glActiveTexture(GL_TEXTURE0);
	
	float temp_x = x;
	for (auto c : text)
	{
		Character ch = (*mFontData)[c];
		GLfloat xpos = temp_x + ch.mBearing.x * scale;
		GLfloat ypos = y - (ch.mSize.y - ch.mBearing.y) * scale;
		GLfloat w = ch.mSize.x * scale;
		GLfloat h = ch.mSize.y * scale;
		GLfloat verts[6][4] =
		{
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		glBindTexture(GL_TEXTURE_2D, ch.mTextureId);
		glBindBuffer(GL_ARRAY_BUFFER, mVboId);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		temp_x += (ch.mAdvance >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	mShader->UnUse();
}


void Font::Init()
{
	glGenVertexArrays(1, &mVaoId);
	glGenBuffers(1, &mVboId);
	glBindVertexArray(mVaoId);
	glBindBuffer(GL_ARRAY_BUFFER, mVboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	mShader->Use();
	mShader->AddAttribute(DFLT_VERTEX_ATTRIB_NAME);
	mShader->UnUse();
	glEnableVertexAttribArray((*mShader)[DFLT_VERTEX_ATTRIB_NAME]);
	glVertexAttribPointer((*mShader)[DFLT_VERTEX_ATTRIB_NAME], 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Font::Destroy()
{
	glDeleteBuffers(1, &mVboId);
	glDeleteVertexArrays(1, &mVaoId);
}

const GLuint& Font::GetVao() const
{
	return mVaoId;
}
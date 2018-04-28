#include"engine/objects/Canvas.h"

Canvas::Canvas() :
	mShader(ShaderProgram()),
	mProjection(glm::mat4(1.0f)),
	mFont(nullptr),
	mVaoId(0),
	mVboVerticesId(0)
{

}

Canvas::~Canvas()
{
	Destroy();
}

void Canvas::Init()
{
	mFont->Init();
	mShader.LoadFromFile(ShaderProgram::VERTEX, "C:\\EBS\\OpenGL\\shaders\\font.vert");
	mShader.LoadFromFile(ShaderProgram::FRAGMENT, "C:\\EBS\\OpenGL\\shaders\\font.frag");
	mShader.CreateAndLink();
	mShader.Use();
	//mShader.AddAttribute("vVertex");
	mShader.AutoFillUniformsFromFile("C:\\EBS\\OpenGL\\shaders\\font.vert");
	mShader.AutoFillUniformsFromFile("C:\\EBS\\OpenGL\\shaders\\font.frag");
	glGenVertexArrays(1, &mVaoId);
	glGenBuffers(1, &mVboVerticesId);


	glBindVertexArray(mVaoId);
	glBindBuffer(GL_ARRAY_BUFFER, mVboVerticesId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 24, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(mShader["vVertex"]);
	glVertexAttribPointer(mShader["vVertex"], 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	mProjection = glm::ortho(0.0f, ScreenWidth(), 0.0f, ScreenHeight());
	glUniformMatrix4fv(mShader("Projection"), 1, GL_FALSE, glm::value_ptr(mProjection));
	mShader.UnUse();
}


void Canvas::Destroy()
{
	mShader.DeleteProgram();
	glDeleteBuffers(1, &mVboVerticesId);
	glDeleteVertexArrays(1, &mVaoId);
}


void Canvas::Render(const std::string& text, const GLfloat& x, const GLfloat& y, const GLfloat& scale, const glm::vec3& color)
{
	mShader.Use();
	GLint prev_poly_mode;
	glGetIntegerv(GL_POLYGON_MODE, &prev_poly_mode);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glUniform3fv(mShader("TextColor"), 1, glm::value_ptr(color));
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(mVaoId);
	mFont->Draw(text, x, y, scale);
	/*float temp_x = x;
	for (auto c : text)
	{
		Character ch = mFont->operator[](c);
		GLfloat xpos = temp_x + ch.mBearing.x * scale;
		GLfloat ypos = y - (ch.mSize.y - ch.mBearing.y) * scale;
		GLfloat w = ch.mSize.x * scale;
		GLfloat h = ch.mSize.y * scale;
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		glBindTexture(GL_TEXTURE_2D, ch.mTextureId);
		glBindBuffer(GL_ARRAY_BUFFER, mVboVerticesId);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		temp_x += (ch.mAdvance >> 6) * scale;
	}*/

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPolygonMode(GL_FRONT_AND_BACK, prev_poly_mode);
	mShader.UnUse();

}

#include"engine/objects/RenderableObject.h"
namespace sd_app {
namespace engine {
namespace objects {
namespace impl {
namespace renderable_object {
RenderableObject::RenderableObject() :
	mVaoId(0),
	mVboVerticesId(0),
	mVboIndicesId(0),
	mShader(ShaderProgram()),
	mPrimitiveType(GL_TRIANGLES),
	mTotalVertices(0),
	mTotalIndices(0),
	mColor(0.0f, 0.0f, 0.0f, 1.0f)
{

}

RenderableObject::~RenderableObject()
{
	Destroy();
}

void RenderableObject::Render(const float* MVP)
{
	mShader.Use();
	glUniformMatrix4fv(mShader("MVP"), 1, GL_FALSE, MVP);
	SetCustomUniforms();
	glBindVertexArray(mVaoId);
	GLint prev_poly_mode;
	glGetIntegerv(GL_POLYGON_MODE, &prev_poly_mode);
	glPolygonMode(GL_FRONT_AND_BACK, mPolygonMode);
	glDrawElements(mPrimitiveType, mTotalIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, prev_poly_mode);
	mShader.UnUse();
}

void RenderableObject::SetCustomUniforms()
{
	glUniform4fv(mShader("Color"), 1, glm::value_ptr(mColor));
}

void RenderableObject::Color(const glm::vec4& color)
{
	mColor = color;
}

glm::vec4 RenderableObject::Color() const
{
	return mColor;
}

void RenderableObject::AddCustomAttribs()
{
	mShader.AddAttribute("vVertex");
}

void RenderableObject::Init()
{

	mShader.LoadFromFile(ShaderProgram::VERTEX, VertexShaderPath());
	mShader.LoadFromFile(ShaderProgram::FRAGMENT, FragmentShaderPath());
	mShader.CreateAndLink();
	mShader.Use();
	AddCustomAttribs();
	mShader.AutoFillUniformsFromFile(VertexShaderPath());
	mShader.AutoFillUniformsFromFile(FragmentShaderPath());
	SetCustomUniforms();
	mShader.UnUse();

	glGenVertexArrays(1, &mVaoId);
	glGenBuffers(1, &mVboVerticesId);
	glGenBuffers(1, &mVboIndicesId);

	mTotalVertices = GetTotalVertices();
	mTotalIndices = GetTotalIndices();
	mPrimitiveType = GetPrimitiveType();
	mPolygonMode = GetPolygonMode();
	glBindVertexArray(mVaoId);
	glBindBuffer(GL_ARRAY_BUFFER, mVboVerticesId);
	glBufferData(GL_ARRAY_BUFFER, mTotalVertices * sizeof(glm::vec3), 0, GL_STATIC_DRAW);
	GLfloat* buffer = static_cast<GLfloat*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	FillVertexBuffer(buffer);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glEnableVertexAttribArray(mShader["vVertex"]);
	glVertexAttribPointer(mShader["vVertex"], 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVboIndicesId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mTotalIndices * sizeof(GLuint), 0, GL_STATIC_DRAW);
	GLuint* index_buffer = static_cast<GLuint*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
	FillIndexBuffer(index_buffer);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	glBindVertexArray(0);

}

void RenderableObject::Destroy()
{
	mShader.DeleteProgram();
	glDeleteBuffers(1, &mVboVerticesId);
	glDeleteBuffers(1, &mVboIndicesId);
	glDeleteVertexArrays(1, &mVaoId);
}

GLenum RenderableObject::GetPolygonMode()
{
	return GL_LINE;
}

std::string RenderableObject::VertexShaderPath()
{
	return EngineShaderPath("position.vert");
}

std::string RenderableObject::FragmentShaderPath()
{
	return EngineShaderPath("unicolor.frag");
}
} // namespace renderable_object
} // namespace impl
using RenderableObject = impl::renderable_object::RenderableObject;
} // namespace objects
} // namespace engine
} // namespace sd_app
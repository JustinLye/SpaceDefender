#include"engine/shapes/Triangle.h"

Triangle::Triangle() :
	Shape()
{
	Init();
}

Triangle::~Triangle()
{

}

unsigned int Triangle::VertCount()
{
	return 3;
}

unsigned int Triangle::IndexCount()
{
	return 3;
}

GLenum Triangle::PrimType()
{
	return GL_TRIANGLES;
}

void Triangle::FillVertices(GLfloat* buffer)
{
	glm::vec3* verts = (glm::vec3*)buffer;
	verts[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
	verts[1] = glm::vec3(0.0f, 1.0f, 0.0f);
	verts[2] = glm::vec3(1.0f, -1.0f, 0.0f);
}

void Triangle::FillIndices(GLuint* buffer)
{
	GLuint* id = buffer;
	*id++ = 0;
	*id++ = 1;
	*id++ = 2;
}
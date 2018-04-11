#include"engine/shapes/Quad.h"

Quad::Quad() :
	Shape()
{
	Init();
}

Quad::~Quad()
{

}

unsigned int Quad::VertCount()
{
	return 4;
}

unsigned int Quad::IndexCount()
{
	return 6;
}

GLenum Quad::PrimType()
{
	return GL_TRIANGLES;
}

void Quad::FillVertices(GLfloat* buffer)
{
	glm::vec3* verts = (glm::vec3*)buffer;
	verts[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
	verts[1] = glm::vec3(-1.0f, 1.0f, 0.0f);
	verts[2] = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[3] = glm::vec3(1.0f, -1.0f, 0.0f);
}

void Quad::FillIndices(GLuint* buffer)
{
	GLuint* id = buffer;
	*id++ = 0;
	*id++ = 1;
	*id++ = 2;
	*id++ = 0;
	*id++ = 3;
	*id++ = 2;
}

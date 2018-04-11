#include"engine/shapes/Circle.h"

Circle::Circle() :
	Shape()
{
	Init();
}

Circle::~Circle()
{

}

unsigned int Circle::VertCount()
{
	return 36;
}

unsigned int Circle::IndexCount()
{
	return 37;
}

GLenum Circle::PrimType()
{
	return GL_LINE_STRIP;
}

void Circle::FillVertices(GLfloat* buffer)
{
	glm::vec3* verts = (glm::vec3*)buffer;
	for (int i = 0; i < 36; ++i)
	{
		float rads = glm::radians((float)(i + 1)*10.0f);
		verts[i].x = glm::cos(rads);
		verts[i].y = glm::sin(rads);
		verts[i].z = 0.0f;
	}
}

void Circle::FillIndices(GLuint* buffer)
{
	GLuint* id = buffer;
	for (int i = 0; i < 36; ++i)
	{
		*id++ = i;
	}
	*id = 0;
}

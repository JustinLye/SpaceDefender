#include"engine/shapes/LineSegment.h"

LineSegment::LineSegment() :
	Shape()
{
	Init();
}

LineSegment::~LineSegment()
{

}

unsigned int LineSegment::VertCount()
{
	return 2;
}
unsigned int LineSegment::IndexCount()
{
	return 2;
}

GLenum LineSegment::PrimType()
{
	return GL_LINE;
}

void LineSegment::FillVertices(GLfloat* buffer)
{
	glm::vec3* verts = (glm::vec3*)buffer;
	verts[0] = glm::vec3(0.0f, 1.0f, 0.0f);
	verts[1] = glm::vec3(0.0f, -1.0f, 0.0f);
}
void LineSegment::FillIndices(GLuint* buffer)
{
	GLuint* id = buffer;
	*id++ = 0;
	*id++ = 1;
}


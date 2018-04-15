#include"engine/shapes/LineSegmentData.h"

LineSegmentData::LineSegmentData() :
	ShapeData()
{
	Init();
}

LineSegmentData::~LineSegmentData()
{

}

unsigned int LineSegmentData::VertCount()
{
	return 2;
}
unsigned int LineSegmentData::IndexCount()
{
	return 2;
}

GLenum LineSegmentData::PrimType()
{
	return GL_LINE_STRIP;
}

void LineSegmentData::InitializeData()
{
#ifdef ENGINE_DEBUG
	assert(mVertices != nullptr);
	assert(mIndices != nullptr);
#endif
	mVertices[0] = glm::vec3(0.0f, 1.0f, 0.0f);
	mVertices[1] = glm::vec3(0.0f, -1.0f, 0.0f);
	mIndices[0] = 0;
	mIndices[1] = 1;
}
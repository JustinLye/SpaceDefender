#include"engine/shapes/QuadData.h"

QuadData::QuadData() :
	ShapeData()
{
	Init();
}

QuadData::~QuadData()
{

}

unsigned int QuadData::VertCount()
{
	return 4;
}

unsigned int QuadData::IndexCount()
{
	return 6;
}

GLenum QuadData::PrimType()
{
	return GL_TRIANGLES;
}

void QuadData::InitializeData()
{
#ifdef ENGINE_DEBUG
	assert(mVertices != nullptr);
	assert(mIndices != nullptr);
#endif
	mVertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
	mVertices[1] = glm::vec3(-1.0f, 1.0f, 0.0f);
	mVertices[2] = glm::vec3(1.0f, 1.0f, 0.0f);
	mVertices[3] = glm::vec3(1.0f, -1.0f, 0.0f);
	
	mIndices[0] = 0;
	mIndices[1] = 1;
	mIndices[2] = 2;
	mIndices[3] = 0;
	mIndices[4] = 3;
	mIndices[5] = 2;
}
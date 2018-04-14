#include"engine/shapes/ShapeData.h"

ShapeData::ShapeData() :
	mVertices(nullptr),
	mIndices(nullptr)
{

}

ShapeData::~ShapeData()
{
	try
	{
		Destroy();
	}
	catch (...)
	{

	}
}

void ShapeData::FillVertices(GLfloat* buffer)
{
#ifdef ENGINE_DEBUG
	assert(mVertices != nullptr);
#endif
	unsigned int size = VertCount();
	glm::vec3* verts = (glm::vec3*)buffer;
	for (unsigned int i = 0; i < size; ++i)
	{
		verts[i] = mVertices[i];
	}
}

void ShapeData::FillIndices(GLuint* buffer)
{
#ifdef ENGINE_DEBUG
	assert(mIndices != nullptr);
#endif
	unsigned int size = IndexCount();
	GLuint* id = buffer;
	for (unsigned int i = 0; i < size; ++i)
	{
		buffer[i] = mIndices[i];
	}
}

void ShapeData::Init()
{
	InitializePointers();
	InitializeData();
}

void ShapeData::InitializePointers()
{
#ifdef ENGINE_DEBUG
	assert(mVertices == nullptr);
	assert(mIndices == nullptr);
#endif
	mVertices = new glm::vec3[VertCount()];
	mIndices = new GLuint[IndexCount()];
}

void ShapeData::Destroy()
{
	if (mVertices != nullptr)
	{
		delete[] mVertices;
	}
	if (mIndices != nullptr)
	{
		delete[] mIndices;
	}
	
}
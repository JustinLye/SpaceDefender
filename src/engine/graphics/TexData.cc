#include"engine/graphics/TexData.h"
namespace sd_app {
namespace engine {
namespace graphics {
namespace impl {
namespace tex_data {
TexData::TexData() :
	mTexVertexData(nullptr),
	mIndices(nullptr)
{

}

TexData::~TexData()
{
	try
	{
		Destroy();
	}
	catch (...)
	{

	}
}

void TexData::FillVertices(GLfloat* buffer)
{
	unsigned int size = VertCount();
	TexVertexData* verts = (TexVertexData*)buffer;
	for (unsigned int i = 0; i < size; ++i)
	{
		verts[i] = mTexVertexData[i];
	}
}

void TexData::FillIndices(GLuint* buffer)
{
	unsigned int size = IndexCount();
	GLuint* id = buffer;
	for (unsigned int i = 0; i < size; ++i)
	{
		buffer[i] = mIndices[i];
	}
}

void TexData::Init()
{
	InitializePointers();
	InitializeData();
}

void TexData::InitializePointers()
{
	mTexVertexData = new TexVertexData[VertCount()];
	mIndices = new GLuint[IndexCount()];
}

void TexData::Destroy()
{
	if (mTexVertexData != nullptr)
	{
		delete[] mTexVertexData;
		mTexVertexData = nullptr;
	}
	if (mIndices != nullptr)
	{
		delete[] mIndices;
		mTexVertexData = nullptr;
	}
}
} // namespace tex_data
} // namespace impl
} // namespace graphics
} // namespace engine
} // namespace ad_app
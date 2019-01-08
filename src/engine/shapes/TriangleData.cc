#include"engine/shapes/TriangleData.h"
namespace sd_app {
namespace engine {
namespace shapes {
namespace impl {
namespace triangle_data {
TriangleData::TriangleData() :
	ShapeData()
{
	Init();
}

TriangleData::~TriangleData()
{

}

unsigned int TriangleData::VertCount()
{
	return 3;
}

unsigned int TriangleData::IndexCount()
{
	return 3;
}

GLenum TriangleData::PrimType()
{
	return GL_TRIANGLES;
}

void TriangleData::InitializeData()
{
#ifdef ENGINE_DEBUG
	assert(mVertices != nullptr);
	assert(mIndices != nullptr);

#endif
	mVertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
	mVertices[1] = glm::vec3(0.0f, 1.0f, 0.0f);
	mVertices[2] = glm::vec3(1.0f, -1.0f, 0.0f);
	mIndices[0] = 0;
	mIndices[1] = 1;
	mIndices[2] = 2;
}
} // namespace triangle_data
} // namespace impl
} // namespace shapes
} // namespace engine
} // namespace sd_app
#include"engine/shapes/QuadData.h"
namespace sd_app {
namespace engine {
namespace shapes {
namespace impl {
namespace quad_data {
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
} // namespace quad_data
} // namespace impl
} // namespace shapes
} // namespace engine
} // namespace sd_app
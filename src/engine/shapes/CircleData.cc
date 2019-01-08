#include"engine/shapes/CircleData.h"
namespace sd_app {
namespace engine {
namespace shapes {
namespace impl {
namespace circle_data {
CircleData::CircleData() :
	ShapeData()
{
	Init();
}

CircleData::~CircleData()
{

}

unsigned int CircleData::VertCount()
{
	return 36;
}

unsigned int CircleData::IndexCount()
{
	return 37;
}

GLenum CircleData::PrimType()
{
	return GL_LINE_STRIP;
}

void CircleData::InitializeData()
{
#ifdef ENGINE_DEBUG
	assert(mVertices != nullptr);
	assert(mIndices != nullptr);
#endif
	unsigned int vert_size = VertCount();
	for (unsigned int i = 0; i < vert_size; ++i)
	{
		float rads = glm::radians((float)(i + 1)*10.0f);
		mVertices[i] = glm::vec3(glm::cos(rads), glm::sin(rads), 0.0f);
	}

	unsigned int index_size = IndexCount();
	for (GLuint i = 0; i < index_size-1; ++i)
	{
		mIndices[i] = i;
	}
	mIndices[index_size - 1] = 0;
}
} // namespace circle_data
} // namespace impl
} // namespace shapes
} // namespace engine
} // namespace sd_app
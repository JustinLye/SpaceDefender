
#include"engine/objects/TransformData.h"
namespace sd_app {
namespace engine {
namespace objects {
namespace impl {
namespace transform_data {
TransformData::TransformData() :
	mScale(glm::vec3(1.0f)),
	mPosition(glm::vec3(0.0f)),
	mRotation(glm::quat()),
	mOffset(glm::vec3(0.0f)) {}
} // namespace transform_data
} // namespace impl
} // namespace objects
} // namespace engine
} // namespace sd_app
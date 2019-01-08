#ifndef TRANSFORM_DATA_HEADER_INCLUDED
#define TRANSFORM_DATA_HEADER_INCLUDED

#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>
namespace sd_app {
namespace engine {
namespace objects {
namespace impl {
namespace transform_data {
/** @addtogroup EngineObjects */
/*@{*/
struct TransformData {
  TransformData();
  glm::vec3 mScale;
  glm::vec3 mPosition;
  glm::quat mRotation;
  glm::vec3 mOffset;
};
/*@}*/
} // namespace transform_data
} // namespace impl
using TransformData = impl::transform_data::TransformData;
} // namespace objects
} // namespace engine
} // namespace sd_app

#endif
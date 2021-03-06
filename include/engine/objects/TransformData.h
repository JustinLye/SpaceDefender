#ifndef TRANSFORM_DATA_HEADER_INCLUDED
#define TRANSFORM_DATA_HEADER_INCLUDED

#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>

/** @addtogroup EngineObjects */
/*@{*/
struct TransformData
{
	TransformData();
	glm::vec3 mScale;
	glm::vec3 mPosition;
	glm::quat mRotation;
	glm::vec3 mOffset;
};
/*@}*/
#endif
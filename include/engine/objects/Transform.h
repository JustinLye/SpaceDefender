#ifndef TRANSFORM_HEADER_INCLUDED
#define TRANSFORM_HEADER_INCLUDED

#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>

struct Transform
{
	Transform();
	glm::vec3 mScale;
	glm::vec3 mPosition;
	glm::quat mRotation;
};

#endif
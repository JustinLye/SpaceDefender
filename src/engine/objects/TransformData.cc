#include"engine/objects/TransformData.h"

TransformData::TransformData() :
	mScale(glm::vec3(1.0f)),
	mPosition(glm::vec3(0.0f)),
	mRotation(glm::quat()),
	mOffset(glm::vec3(0.0f))
{

}
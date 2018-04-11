#include"engine/objects/Transform.h"

Transform::Transform() :
	mScale(glm::vec3(1.0f)),
	mPosition(glm::vec3(0.0f)),
	mRotation(glm::quat())
{

}
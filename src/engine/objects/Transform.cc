#include"engine/objects/Transform.h"

Transform::Transform()
{

}

Transform::~Transform()
{

}

void Transform::Scale(const glm::vec3& scale)
{
	mTransformData.mScale *= scale;
}

const glm::vec3& Transform::Scale() const
{
	return mTransformData.mScale;
}

void Transform::Translate(const glm::vec3& translation_vec)
{
	mTransformData.mPosition += translation_vec;
}

const glm::vec3& Transform::Position() const
{
	return mTransformData.mPosition;
}

void Transform::Rotate(const float& angle_degrees, const glm::vec3& rotation_axis)
{
	mTransformData.mRotation = glm::rotate(mTransformData.mRotation, angle_degrees, rotation_axis);
}

void Transform::Rotation(const glm::quat& copy_quat)
{
	mTransformData.mRotation = copy_quat;
}

const glm::quat& Transform::Rotation() const
{
	return mTransformData.mRotation;
}

glm::mat4 Transform::Model()
{
	glm::mat4 translation_matrix = glm::translate(Constants::Geometry::IDENTITY_MATRIX, mTransformData.mPosition);
	glm::mat4 scale_matrix = glm::scale(Constants::Geometry::IDENTITY_MATRIX, mTransformData.mScale);
	glm::mat4 rotation_matrix = glm::mat4_cast(mTransformData.mRotation);
	return translation_matrix * rotation_matrix * scale_matrix;
}
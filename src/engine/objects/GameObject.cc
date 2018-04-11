#include"engine/objects/GameObject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::Scale(const glm::vec3& scale)
{
	mTransform.mScale *= scale;
}

const glm::vec3& GameObject::Scale() const
{
	return mTransform.mScale;
}

void GameObject::Translate(const glm::vec3& translation_vec)
{
	mTransform.mPosition += translation_vec;
}

const glm::vec3& GameObject::Position() const
{
	return mTransform.mPosition;
}

void GameObject::Rotate(const float& angle_degrees, const glm::vec3& rotation_axis)
{
	mTransform.mRotation = glm::rotate(mTransform.mRotation, angle_degrees, rotation_axis);
}

const glm::quat& GameObject::Rotation() const
{
	return mTransform.mRotation;
}

glm::mat4 GameObject::Model()
{
	glm::mat4 translation_matrix = glm::translate(Constants::Geometry::IDENTITY_MATRIX, mTransform.mPosition);
	glm::mat4 scale_matrix = glm::scale(Constants::Geometry::IDENTITY_MATRIX, mTransform.mScale);
	glm::mat4 rotation_matrix = glm::mat4_cast(mTransform.mRotation);
	return translation_matrix * rotation_matrix * scale_matrix;
}
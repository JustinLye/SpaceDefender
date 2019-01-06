#include"engine/objects/Transform.h"

Transform::Transform()
{

}

Transform::Transform(const Transform& other) :
	mTransformData(other.mTransformData)
{

}

Transform::~Transform()
{

}

void Transform::Scale(float scale)
{
	mTransformData.mScale *= scale;
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
	//mTransformData.mOffset += translation_vec;
}

const glm::vec3& Transform::Position() const
{
	return mTransformData.mPosition;
}

void Transform::Rotate(float angle_degrees, const glm::vec3& rotation_axis)
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

void Transform::Offset(const glm::vec3& offset_vec)
{
	mTransformData.mOffset += offset_vec;
}

const glm::vec3& Transform::Offset() const
{
	return mTransformData.mOffset;
}

glm::mat4 Transform::Model()
{
	glm::mat4 translation_matrix = glm::translate(Constants::Geometry::IDENTITY_MATRIX, mTransformData.mPosition);
	glm::mat4 offset_matrix = glm::translate(Constants::Geometry::IDENTITY_MATRIX, mTransformData.mOffset);
	glm::mat4 scale_matrix = glm::scale(Constants::Geometry::IDENTITY_MATRIX, mTransformData.mScale);
	glm::mat4 rotation_matrix = glm::mat4_cast(mTransformData.mRotation);
	return  translation_matrix * rotation_matrix * offset_matrix * scale_matrix;
	//return  translation_matrix * rotation_matrix * scale_matrix;
}

void Transform::Match(const Transform& other)
{
	mTransformData.mPosition = other.Position();
	mTransformData.mRotation = other.Rotation();
	mTransformData.mScale = other.Scale();
	mTransformData.mOffset = other.Offset();
}

void Transform::JumpToPosition(const Transform& other)
{
	mTransformData.mPosition = other.Position();
}

void Transform::JumpToPosition(const glm::vec3& pos)
{
	mTransformData.mPosition = pos;
}

void Transform::ResetScale()
{
	mTransformData.mScale *= 1.0f / mTransformData.mScale;
}

Transform& Transform::operator=(const Transform& other)
{
	this->mTransformData = other.mTransformData;
	return *this;
}

bool Transform::operator<(const Transform& other) const
{
	if (mTransformData.mPosition.x < other.Position().x)
	{
		return true;
	}
	else if (mTransformData.mPosition.x > other.Position().x)
	{
		return false;
	}
	if (mTransformData.mPosition.y < other.Position().y)
	{
		return true;
	}
	else if (mTransformData.mPosition.y > other.Position().y)
	{
		return false;
	}

	if (mTransformData.mPosition.z < other.Position().z)
	{
		return true;
	}
	else if (mTransformData.mPosition.z > other.Position().z)
	{
		return false;
	}

	return false;
}

Transform::operator std::string() const
{
	return ToString();
}

std::ostream& operator<<(std::ostream& out, const Transform& transform)
{
	transform.Output(out);
	return out;
}

std::string& operator+(std::string& str, const Transform& transform)
{
	return str += transform.ToString();
}

void Transform::Output(std::ostream& out) const
{
	out << ToString() << '\n';
	/*out << "pos: [" << mTransformData.mPosition.x << ", " << mTransformData.mPosition.y << ", " << mTransformData.mPosition.z << "]";
	out << "\tscale: [" << mTransformData.mScale.x << ", " << mTransformData.mScale.y << ", " << mTransformData.mScale.z << "]";
	out << "\toffset: [" << mTransformData.mOffset.x << ", " << mTransformData.mOffset.y << ", " << mTransformData.mOffset.z << "]";
	out << "\trotation: [" << mTransformData.mRotation.x << ", " << mTransformData.mRotation.y << ", " << mTransformData.mRotation.z << ", " << mTransformData.mRotation.w << "]\n";*/
}

std::string Transform::ToString() const
{
	std::string result;
	result = std::string("pos: ") + Vec3ToString(mTransformData.mPosition);
	result += std::string("\tscale: ") + Vec3ToString(mTransformData.mScale);
	result += std::string("\toffset: ") + Vec3ToString(mTransformData.mOffset);
	result += std::string("\trotation: ") + Vec4ToString(mTransformData.mRotation);
	return result;
}

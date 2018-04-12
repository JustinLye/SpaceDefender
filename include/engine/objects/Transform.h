#ifndef TRANSFORM_HEADER_INCLUDED
#define TRANSFORM_HEADER_INCLUDED

#include<glm/gtc/matrix_transform.hpp>
#include"engine/objects/TransformData.h"
#include"engine/util/Constants.h"


class Transform
{
public:
	Transform();
	virtual ~Transform();

	virtual void Scale(const glm::vec3&);
	const glm::vec3& Scale() const;
	virtual void Translate(const glm::vec3&);
	const glm::vec3& Position() const;
	virtual void Rotate(const float&, const glm::vec3&);
	virtual void Rotation(const glm::quat&);
	const glm::quat& Rotation() const;
	glm::mat4 Model();
	
protected:
	TransformData mTransformData;
	glm::mat4 mModel;
};

#endif
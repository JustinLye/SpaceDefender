#ifndef GAME_OBJECT_HEADER_INCLUDED
#define GAME_OBJECT_HEADER_INCLUDED

#include<glm/gtc/matrix_transform.hpp>
#include"engine/objects/Transform.h"
#include"engine/util/Constants.h"


class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Scale(const glm::vec3&);
	const glm::vec3& Scale() const;
	virtual void Translate(const glm::vec3&);
	const glm::vec3& Position() const;
	virtual void Rotate(const float&, const glm::vec3&);
	const glm::quat& Rotation() const;
	glm::mat4 Model();
	
protected:
	Transform mTransform;
	glm::mat4 mModel;
};

#endif
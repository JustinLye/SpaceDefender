#ifndef TRANSFORM_HEADER_INCLUDED
#define TRANSFORM_HEADER_INCLUDED
#include<iostream>
#include<string>
#include<boost/lexical_cast.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"engine/objects/TransformData.h"
#include"engine/util/Constants.h"
#include"engine/util/UtiliDefs.h"


class Transform
{
public:
	Transform();
	Transform(const Transform&);
	virtual ~Transform();

	virtual void Scale(const float&);
	virtual void Scale(const glm::vec3&);
	const glm::vec3& Scale() const;
	virtual void Translate(const glm::vec3&);
	const glm::vec3& Position() const;
	virtual void Rotate(const float&, const glm::vec3&);
	virtual void Rotation(const glm::quat&);
	const glm::quat& Rotation() const;
	virtual void Offset(const glm::vec3&);
	const glm::vec3& Offset() const;
	glm::mat4 Model();
	
	virtual void Match(const Transform&);
	virtual void JumpToPosition(const Transform&);
	virtual void JumpToPosition(const glm::vec3&);
	virtual void ResetScale();
	Transform& operator =(const Transform&);
	bool operator<(const Transform&) const;
	operator std::string() const;
	friend std::ostream& operator<<(std::ostream&, const Transform&);
	friend std::string& operator+(std::string&, const Transform&);

protected:
	TransformData mTransformData;
	glm::mat4 mModel;

	void Output(std::ostream&) const;
	std::string ToString() const;
};

#endif
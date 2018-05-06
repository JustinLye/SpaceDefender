#include"engine/objects/DrawableObject.h"

DrawableObject::DrawableObject() :
	mVaoId(0)
{

}

DrawableObject::~DrawableObject()
{

}

void DrawableObject::Activate()
{
	glBindVertexArray(mVaoId);
	CustomActivationSteps();
}

void DrawableObject::Deactivate()
{
	glBindVertexArray(0);
	CustomDeactivationSteps();
}

const unsigned int& DrawableObject::GetVAO() const
{
	return mVaoId;
}

unsigned int DrawableObject::GetVAO()
{
	return mVaoId;
}

bool DrawableObject::operator<(const DrawableObject& object) const
{
	return this->mVaoId < object.GetVAO();
}

bool DrawableObject::operator==(const DrawableObject& object) const
{
	return this->mVaoId == object.GetVAO();
}

void DrawableObject::CustomActivationSteps()
{

}

void DrawableObject::CustomDeactivationSteps()
{

}
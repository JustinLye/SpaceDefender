#include"engine/objects/BasicObject.h"

unsigned int BasicObject::sNextBasicObjectId = 0;

BasicObject::BasicObject(const object_t& obj_type) :
	mId(++sNextBasicObjectId),
	mType(obj_type)
{
	DebugMessage(std::string("Next object id: ") + boost::lexical_cast<std::string>(sNextBasicObjectId));
}

BasicObject::~BasicObject()
{

}

const object_t& BasicObject::Type() const
{
	return mType;
}

const unsigned int& BasicObject::Id() const
{
	return mId;
}

bool BasicObject::operator<(const BasicObject& other) const
{
	return mId < other.Id();
}

bool BasicObject::operator==(const BasicObject& other) const
{
	return mId == other.Id();
}

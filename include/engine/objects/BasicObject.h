#ifndef BASIC_OBJECT_HEADER_INCLUDED
#define BASIC_OBJECT_HEADER_INCLUDED

#include"engine/util/Constants.h"
#include<string>
#include<boost/lexical_cast.hpp>
#include"engine/util/DebugFunctions.h"

using namespace Constants::Types;

class BasicObject
{
public:
	BasicObject(const object_t& = object_t::BASIC_OBJECT);
	virtual ~BasicObject();
	virtual const object_t& Type() const;
	const unsigned int& Id() const;
	bool operator<(const BasicObject&) const;
	bool operator==(const BasicObject&) const;

protected:
	object_t mType;
private:
	static unsigned int sNextBasicObjectId;
	unsigned int mId;

};

#endif
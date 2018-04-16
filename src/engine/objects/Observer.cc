#include"engine/objects/Observer.h"

unsigned int Observer::NextObserverId = 0;

Observer::Observer() :
	mId(++NextObserverId)
{

}

Observer::~Observer()
{

}

const unsigned int& Observer::Id() const
{
	return mId;
}
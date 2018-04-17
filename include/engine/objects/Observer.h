#ifndef OBSERVER_HEADER_INCLUDED
#define OBSERVER_HEADER_INCLUDED

#include"engine/util/Constants.h"
class GameObject;
class Observer
{
public:
	Observer();
	~Observer();

	const unsigned int& Id() const;

	virtual void OnNotify(const GameObject&, const Constants::Types::event_t&) = 0;

private:
	static unsigned int NextObserverId;
	unsigned int mId;

};

#endif
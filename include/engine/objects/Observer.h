#ifndef OBSERVER_HEADER_INCLUDED
#define OBSERVER_HEADER_INCLUDED

#include"engine/util/Constants.h"
#include"engine/objects/GameObject.h"

class Observer
{
public:
	typedef Constants::event_t event_t;
	Observer();
	~Observer();

	const unsigned int& Id() const;

	virtual void OnNotify(const GameObject&, const event_t&) = 0;

private:
	static unsigned int NextObserverId;
	unsigned int mId;

};

#endif
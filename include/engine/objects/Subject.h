#ifndef SUBJECT_HEADER_INCLUDED
#define SUBJECT_HEADER_INCLUDED

#include<map>
#include"engine/objects/Observer.h"

class Subject
{
public:
	Subject();
	~Subject();
	virtual void AddObserver(Observer*);
	virtual void RemoveObserver(Observer*);
	virtual void Notify(const GameObject&, const Constants::event_t&);
protected:
	std::map<unsigned int, Observer*> mObserverMap;
	bool ObserverIsMapped(Observer*) const;
};

#endif
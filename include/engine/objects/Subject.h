#ifndef SUBJECT_HEADER_INCLUDED
#define SUBJECT_HEADER_INCLUDED
#ifdef ENGINE_DEBUG
#include<iostream>
#endif
#include<map>
#include"engine/util/Constants.h"
#include"engine/objects/Observer.h"


/** @addtogroup EngineObjects */
/*@{*/

/*!
  \brief Observered by zero or more Observers
*/
class Subject
{
public:
	Subject();
	~Subject();
	virtual void AddObserver(Observer*);
	virtual void RemoveObserver(Observer*);
	virtual void Notify(const GameObject&, const Constants::Types::event_t&) const;
protected:
	std::map<unsigned int, Observer*> mObserverMap;
	bool ObserverIsMapped(Observer*) const;
};
/*@}*/
#endif
#include"engine/objects/Subject.h"

Subject::Subject()
{

}

Subject::~Subject()
{

}

void Subject::AddObserver(Observer* observer)
{
	std::cout << __FUNCTION__ << " " << __LINE__ << '\n';
	if (!ObserverIsMapped(observer))
	{
		std::cout << __FUNCTION__ << " " << __LINE__ << '\n';
		mObserverMap.insert({ observer->Id(), observer });
	}
}

void Subject::RemoveObserver(Observer* observer)
{
	mObserverMap.erase(observer->Id());
}

void Subject::Notify(const GameObject& object, const Constants::Types::event_t& event_name) const
{
	std::map<unsigned int, Observer*>::const_iterator iter = mObserverMap.cbegin();
	while (iter != mObserverMap.end())
	{
		iter->second->OnNotify(object, event_name);
		++iter;
	}
}

bool Subject::ObserverIsMapped(Observer* observer) const
{
	return (mObserverMap.find(observer->Id()) != mObserverMap.cend());
}
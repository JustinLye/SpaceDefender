#ifndef SP_APP_SUBJECT_CC_INCLUDED
#define SP_APP_SUBJECT_CC_INCLUDED

#include"core/Subject.h"

namespace sd_app {
namespace core {
namespace impl {
namespace subject {
template<class T>
Subject<T>::Subject() {

}

template<class T>
Subject<T>::~Subject() {

}
template<class T>
void Subject<T>::AddObserver(Observer<T>* observer) {
  if (!ObserverIsMapped(observer)) {
    mObserverMap.insert({ observer->Id(), observer });
  }
}

template<class T>
void Subject<T>::RemoveObserver(Observer<T>* observer) {
  mObserverMap.erase(observer->Id());
}

template<class T>
void Subject<T>::Notify(const T& object, const event_t& event_name) const {
  auto iter = mObserverMap.cbegin();
  while (iter != mObserverMap.end()) {
    iter->second->OnNotify(object, event_name);
    ++iter;
  }
}

template<class T>
bool Subject<T>::ObserverIsMapped(Observer<T>* observer) const {
  return (mObserverMap.find(observer->Id()) != mObserverMap.cend());
}
} // namespace subject
} // namespace impl
} // namespace core
} // namespace sd_app
#endif // !SP_APP_SUBJECT_CC_INCLUDED


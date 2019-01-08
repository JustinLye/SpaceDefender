#include"core/Subject.h"

namespace sd_app {
namespace core {
namespace impl {
namespace subject {
Subject::Subject() {

}

Subject::~Subject() {

}

void Subject::AddObserver(Observer* observer) {
  if (!ObserverIsMapped(observer)) {
    mObserverMap.insert({ observer->Id(), observer });
  }
}

void Subject::RemoveObserver(Observer* observer) {
  mObserverMap.erase(observer->Id());
}

template<class T>
void Subject::Notify(const T& object, const event_t& event_name) const {
  std::map<unsigned int, Observer*>::const_iterator iter = mObserverMap.cbegin();
  while (iter != mObserverMap.end()) {
    iter->second->OnNotify(object, event_name);
    ++iter;
  }
}

bool Subject::ObserverIsMapped(Observer* observer) const {
  return (mObserverMap.find(observer->Id()) != mObserverMap.cend());
}
} // namespace subject
} // namespace impl
} // namespace core
} // namespace sd_app



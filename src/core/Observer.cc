#ifndef OBSERVER_CC_INCLUDED
#define OBSERVER_CC_INCLUDED
#include"core/Observer.h"

namespace sd_app {
namespace core {
namespace impl {
namespace observer {
template<class T>
unsigned int Observer<T>::NextObserverId = 0;

template<class T>
Observer<T>::Observer() :
  mId(++NextObserverId) {

}

template<class T>
Observer<T>::~Observer() {}

template<class T>
unsigned int Observer<T>::Id() const {
  return mId;
}
} // namespace observer
} // namespace impl
} // namespace core
} // namespace sd_app
#endif // !OBSERVER_CC_INCLUDED

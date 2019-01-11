#ifndef SUBJECT_HEADER_INCLUDED
#define SUBJECT_HEADER_INCLUDED
#ifdef ENGINE_DEBUG
#include<iostream>
#endif
#include<map>
#include"engine/util/Constants.h"
#include"core/Observer.h"

namespace sd_app {
namespace core {
namespace impl {
namespace subject {
using event_t = sd_app::engine::constants::types::event_t;

/** @addtogroup Core */
/*@{*/

/*!
  \brief Observered by zero or more Observers
*/
template<class T>
class Subject {
public:
  Subject();
  virtual ~Subject();
  virtual void AddObserver(Observer<T>*);
  virtual void RemoveObserver(Observer<T>*);
  virtual void Notify(const T&, const event_t&) const;
protected:
  std::map<unsigned int, Observer<T>*> mObserverMap;
  bool ObserverIsMapped(Observer<T>*) const;
};

/*@}*/
} // namespace subject
} // namespace impl
template<class T>
using Subject = impl::subject::Subject<T>;
} // namespace core
} // namespace sd_app
#ifndef SP_APP_SUBJECT_CC_INCLUDED
#include"core/Subject.cc"
#endif // !SP_APP_SUBJECT_CC_INCLUDED

#endif
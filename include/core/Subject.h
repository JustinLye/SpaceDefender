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
using Observer = sd_app::core::Observer;

/** @addtogroup Core */
/*@{*/

/*!
  \brief Observered by zero or more Observers
*/
class Subject {
public:
  Subject();
  ~Subject();
  virtual void AddObserver(Observer*);
  virtual void RemoveObserver(Observer*);
  template<class T>
  void Notify(const T&, const event_t&) const;
protected:
  std::map<unsigned int, Observer*> mObserverMap;
  bool ObserverIsMapped(Observer*) const;
};
/*@}*/
#endif

} // namespace subject
} // namespace impl

using Subject = impl::subject::Subject;
} // namespace core
} // namespace sd_app
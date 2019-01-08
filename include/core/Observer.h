
#ifndef OBSERVER_HEADER_INCLUDED
#define OBSERVER_HEADER_INCLUDED

#include"engine/util/Constants.h"


namespace sd_app {
namespace core {
namespace impl {
namespace observer {
using event_t = sd_app::engine::constants::types::event_t;

/** @addtogroup EngineObjects */
/*@{*/

/*!

  \brief Observers Subject class

  Observer is inherited by classes that need to be aware of events generated by other game components (Subject).
  Originally, I wanted to use an event based system that was implemented by running each game component on a separate thread.
  I had trouble with using GLFW on multiple threads. Mainly, I wanted to send an update event to all RenderableObjects running
  on separate threads, then wait for each thread to return some sort of completion event. An update event could trigger several
  subsequent events passed between various components. Needless to say this got very complicated, so I decided to scrap that and
  use an Observer design pattern on a single thread. This has worked well for my needs.

*/
class Observer {
public:
  Observer(); ///< Constructor
  virtual ~Observer() = 0; ///< Destructor

  unsigned int Id() const; ///< Get Observers' unique id.
  template<class T>
  void OnNotify(const T&, const event_t&); ///< Handle event notification.

private:
  static unsigned int NextObserverId; ///< Holds next observer id. Incremented each time an Observer is constructed
  unsigned int mId; ///< Unique id of Observer instance.
};
} // namespace observer
} // namespace impl
using Observer = impl::observer::Observer;
} // namespace core
} // namespace sd_app


/*@}*/

#endif
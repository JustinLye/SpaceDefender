#ifndef __THREAD_H_INCLUDED__
#define __THREAD_H_INCLUDED__


#include<thread>
#include<functional>

#include"core/NonCopyable.h"

namespace sd_app {
namespace engine {
namespace util {
namespace impl {
namespace thread {
using NonCopyable = core::NonCopyable;

/** @addtogroup EngineUtil */
/*@{*/

class Thread :
  private NonCopyable,
  private std::thread {
public:
  using std::thread::get_id;
  using std::thread::join;
  using std::thread::joinable;
  explicit Thread();
  virtual ~Thread();
  virtual void Launch();
  void operator()();
protected:
  virtual void EntryPoint() = 0;

  std::thread::id mThread_id;
};
/*@}*/
} // namespace thread
} // namespace impl
using Thread = impl::thread::Thread;
} // namespace util
} // namespace engine
} // namespace sd_app


#endif

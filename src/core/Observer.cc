#include"core/Observer.h"

namespace sd_app {
namespace core {
namespace impl {
namespace observer {

unsigned int Observer::NextObserverId = 0;

Observer::Observer() :
  mId(++NextObserverId) {

}

template<class T>
void Observer::OnNotify(const T& object, const event_t& event_name) {

}

unsigned int Observer::Id() const {
  return mId;
}

} // namespace observer
} // namespace impl
} // namespace core
} // namespace sd_app


#ifndef DISTANCE_ENTRY_HEADER_INCLUDED
#define DISTANCE_ENTRY_HEADER_INCLUDED

#include<glm/glm.hpp>
#include"engine/objects/GameObject.h"

namespace sd_app {
namespace engine {
namespace util {
namespace impl {
namespace distance_entry {
/** @addtogroup EngineUtil */
/*@{*/
struct DistanceEntry {
  DistanceEntry(const int& = 0, float = 0.0f);
  DistanceEntry(const DistanceEntry&);
  DistanceEntry(DistanceEntry&&);

  bool operator<(const DistanceEntry&) const;
  DistanceEntry& operator=(const DistanceEntry&);

  int mIndex;
  float mDistance;
};
/*@}*/
}// namespace distance_entry
}// namespace impl
using DistanceEntry = impl::distance_entry::DistanceEntry;
}// namespace util
}// namespace engine
}// namespace sd_app


#endif // !DISTANCE_ENTRY_HEADER_INCLUDED

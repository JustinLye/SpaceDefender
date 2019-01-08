#ifndef KEY_MAP_HEADER_INCLUDED
#define KEY_MAP_HEADER_INCLUDED

#include<map>
#include<chrono>
#include"engine/util/Constants.h"

namespace sd_app {
namespace engine {
namespace util {
namespace impl {
namespace key_map {
using namespace constants::input;
using namespace std::chrono;

/** @addtogroup EngineUtil */
/*@{*/
struct KeyState {
  KEY_STATE mState;
  time_point<steady_clock> mLastChanged;
};

class KeyStateMap {
public:
  KeyStateMap();

  void AddKey(const int&);
  void AddKey(const int&, const KeyState&);
  void RemoveKey(const int&);
  KeyState& operator[](const int&);
  typedef std::map<int, KeyState>::iterator iterator;
  typedef std::map<int, KeyState>::const_iterator const_iterator;
  iterator Begin();
  const_iterator Begin() const;
  iterator End();
  const_iterator End() const;
protected:
  std::map<int, KeyState> mStateMap;
};
/*@}*/
} // namespace key_map
} // namespace impl
using KeyState = impl::key_map::KeyState;
using KeyStateMap = impl::key_map::KeyStateMap;
} // namespace util
} // namespace engine
} // namespace sd_app



#endif
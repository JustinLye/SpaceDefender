#ifndef ACTIVE_OBJECT_TRACKER_HEADER_INCLUDED
#define ACTIVE_OBJECT_TRACKER_HEADER_INCLUDED

#include<vector>
#include<set>
#include"core/Observer.h"
#include"engine/objects/GameObject.h"
#include"engine/util/UtiliDefs.h"
#include"engine/util/Logger.h"


namespace sd_app {
namespace game {
namespace impl {
namespace active_object_tracker {
using event_t = engine::constants::types::event_t;
using object_t = engine::constants::types::object_t;
template<class T>
using Observer = core::Observer<T>;
using Transform = engine::objects::Transform;
using GameObject = engine::objects::GameObject;
using Logger = engine::util::Logger;
using Collider = engine::objects::Collider;
using engine::util::TypeToString;

/** @addtogroup GameWorld */
/*@{*/
class ActiveObjectTracker :
  public Observer<GameObject> {
public:
  ActiveObjectTracker();
  ~ActiveObjectTracker();
  void OnNotify(const GameObject&, const event_t&) override;
  const std::vector<const GameObject*>& GetActiveObjectsList() const;
  std::vector<const GameObject*> ObjectScan(const Transform&, const Transform&) const;
  std::vector<const GameObject*> ObjectScan(const Transform&) const;
  void ObjectScan(const Transform&, std::vector<const GameObject*>&) const;
  void ObjectScan(const Transform&, std::vector<const GameObject*>&, const std::set<object_t>&, bool = false) const;
protected:
  std::vector<const GameObject*> mGameObjectList;
  Logger* mLogger;

};
/*@}*/
} // namespace active_object_tracker
} // namespace impl
using ActiveObjectTracker = impl::active_object_tracker::ActiveObjectTracker;
} // namespace game
} // namespace sd_app


#endif // !ACTIVE_OBJECT_TRACKER_HEADER_INCLUDED
